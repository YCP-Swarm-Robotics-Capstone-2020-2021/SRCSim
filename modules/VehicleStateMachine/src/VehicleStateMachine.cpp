/************************************************************/
/*    NAME: Josiah Sam                                              */
/*    ORGN: YCP                                             */
/*    FILE: VehicleStateMachine.cpp                                        */
/*    DATE: 06/08/2020                                         */
/************************************************************/
#include <iterator>
#include "ivp/MBUtils.h"
#include "ivp/ACTable.h"
#include "VehicleStateMachine.h"

using namespace std;

//---------------------------------------------------------
// Constructor

VehicleStateMachine::VehicleStateMachine()
{

    this->currentState = EnumDefs::VehicleStates::STANDBY;
    m_previousState = currentState;
    srand(MOOSTime());
    timeout = rand() % NUM_MAX_TIMEOUT;
    timeout *= 4; //account for the apptick
}

//---------------------------------------------------------
// Destructor

VehicleStateMachine::~VehicleStateMachine()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool VehicleStateMachine::OnNewMail(MOOSMSG_LIST &NewMail)
{
AppCastingMOOSApp::OnNewMail(NewMail);

MOOSMSG_LIST::iterator p;
for(p=NewMail.begin(); p!=NewMail.end(); p++) {
 CMOOSMsg &msg = *p;
 string key    = msg.GetKey();

#if 0 // Keep these around just for template
 string comm  = msg.GetCommunity();
 double dval  = msg.GetDouble();
 string sval  = msg.GetString();
 string msrc  = msg.GetSource();
 double mtime = msg.GetTime();
 bool   mdbl  = msg.IsDouble();
 bool   mstr  = msg.IsString();
#endif

  if(key == "Change_State")
    onChangeState(msg);
  else if(key == "Reg_Ack")
      registered = true;
  else if(key == "BOUND_DETECT"){
      m_currentBoundaryState = (msg.GetAsString()=="TRUE");
      if(currentState == EnumDefs::VehicleStates::TELEOP and currentState == EnumDefs::STANDBY and currentState == EnumDefs::ALLSTOP){
          return true;
      }
      if( m_currentBoundaryState == true and m_previousBoundaryState == false){
          if(currentState != EnumDefs::VehicleStates::TELEOP and currentState != EnumDefs::BOUNDARY and currentState != EnumDefs::STANDBY and currentState != EnumDefs::ALLSTOP){
              m_previousState = currentState;
              currentState = EnumDefs::VehicleStates::BOUNDARY;
              m_previousBoundaryState = m_currentBoundaryState;
          }
      } else if (m_currentBoundaryState == true and m_previousBoundaryState == true){
          if(currentState != EnumDefs::VehicleStates::BOUNDARY and currentState != EnumDefs::TELEOP and currentState != EnumDefs::ALLSTOP && m_previousState != EnumDefs::VehicleStates::STANDBY){
              Notify("WCA_MESSAGE", "ID="+msg.GetCommunity()+", Level="+QString::number(EnumDefs::StatusState::WARNING).toStdString()+", Message=Boundary Detection failed. Did not go into boundary detection correctly.");
              m_previousState = currentState;
              currentState = EnumDefs::VehicleStates::ALLSTOP;
              m_previousBoundaryState = m_currentBoundaryState;
          }
      } else if (m_currentBoundaryState == false and m_previousBoundaryState == true){
          if(currentState != EnumDefs::TELEOP){
            m_previousState = currentState;
            currentState = EnumDefs::VehicleStates::ALLSTOP;
            m_previousBoundaryState = m_currentBoundaryState;
          }
      }
  }
  else if(key == "OBJECT_DETECTED"){
      EnumDefs::SensorState state = (EnumDefs::SensorState)msg.GetDouble();
      switch(state){
          case EnumDefs::NONE:
               if(dodgeon){
                   currentState = m_previousState;
                   dodgeon = false;
               }
               break;
          default:
               //if((!dodgeon) && ( currentState == EnumDefs::SWARMRUN || currentState == EnumDefs::BOUNDARY || currentState == EnumDefs::DODGE || currentState == EnumDefs::DEMOMODE )){
                if(!dodgeon){
                   if(currentState == EnumDefs::STANDBY || currentState == EnumDefs::ALLSTOP || currentState == EnumDefs::TELEOP || currentState == EnumDefs::SWARMINIT || currentState == EnumDefs::SWARMSTANDBY){
                       break;
                   }
                   else{
                       m_previousState = currentState;
                       currentState = EnumDefs::VehicleStates::DODGE;
                       dodgeon = true;
                   }
               }

               break;
      }
  }
  else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
    reportRunWarning("Unhandled Mail: " + key);
}

return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool VehicleStateMachine::OnConnectToServer()
{
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool VehicleStateMachine::Iterate()
{
AppCastingMOOSApp::Iterate();
// Do your thing here!
//AppCastingMOOSApp::PostReport();
if(count % (int)timeout == 0){
    onPingTimeout();
}
if(!registered){
    Notify("Reg_In", "id="+id.toStdString(), MOOSTime());
}
std::string override = (currentState == EnumDefs::TELEOP) ? "true" : "false";
Notify("OVERRIDE_ON", override, MOOSTime());
Notify("Current_State", QString::fromStdString("State = "+to_string(currentState)).toStdString()+", id="+id.toStdString(), MOOSTime());
Notify("Narwhal_Current_State", "State="+QString::number(currentState).toStdString()+", id="+id.toStdString(), MOOSTime());
Notify("id", id.toStdString(), MOOSTime());
count++;
return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool VehicleStateMachine::OnStartUp()
{
AppCastingMOOSApp::OnStartUp();

STRING_LIST sParams;
m_MissionReader.EnableVerbatimQuoting(false);
if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
 reportConfigWarning("No config block found for " + GetAppName());

STRING_LIST::iterator p;
for(p=sParams.begin(); p!=sParams.end(); p++) {
 string orig  = *p;
 string line  = *p;
 string param = tolower(biteStringX(line, '='));
 string value = line;

 bool handled = false;
 if(param == "id") {
   id = QString::fromStdString(value);
   Notify("id", id.toStdString(), MOOSTime());
   handled = true;
 }
 else if(param == "bar") {
   handled = true;
 }
 if(!handled)
   reportUnhandledConfigWarning(orig);

}

registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void VehicleStateMachine::registerVariables()
{
AppCastingMOOSApp::RegisterVariables();
// Register("FOOBAR", 0);
    Register("Change_State");
    Register("Reg_Ack");
    Register("BOUND_DETECT");
    Register("OBJECT_DETECTED");
}


//------------------------------------------------------------
// Procedure: buildReport()

bool VehicleStateMachine::buildReport()
{
m_msgs << "============================================" << endl;
m_msgs << "File:                                       " << endl;
m_msgs << "============================================" << endl;

ACTable actab(4);
actab << "Alpha | Bravo | Charlie | Delta";
actab.addHeaderLines();
actab << "one" << "two" << "three" << "four";
m_msgs << actab.getFormattedString();

return(true);
}

bool VehicleStateMachine::onChangeState(CMOOSMsg &Msg)
{
    EnumDefs::VehicleStates updateState = currentState;
    if(!Msg.IsString()){
        return MOOSFail("You did not input a string for the Speed_Curv message.");
    }
    int state = 0;
    if(!MOOSValFromString(state, Msg.GetString(), "State")){
        return MOOSFail("VehicleStateMachine: Unable to get State variable from Change_State message.");
    }
    if(state < EnumDefs::VehicleStates::ENUMLAST && state >= 0 && state != EnumDefs::UILAST){
        if (state == EnumDefs::ALLSTOP){
            updateState = EnumDefs::ALLSTOP;
        }
        else if(state == EnumDefs::SWARMMODE && currentState == EnumDefs::STANDBY){
            updateState = EnumDefs::SWARMINIT;
        }
        else if(state == EnumDefs::SWARMRUN && currentState == EnumDefs::SWARMSTANDBY){
            updateState = EnumDefs::SWARMRUN;
        }
        else if(state == EnumDefs::SWARMSTANDBY && (currentState == EnumDefs::SWARMINIT || currentState == EnumDefs::SWARMRUN)){
            updateState = EnumDefs::SWARMSTANDBY;
        }
        else if(currentState == EnumDefs::STANDBY || state == EnumDefs::STANDBY ){
            updateState = EnumDefs::VehicleStates(state);
        }
    } else {
        return MOOSDebugWrite("VehicleStateMachine: Received a Change_State message that contains an invalid state.");
    }
    m_previousState = currentState;
    currentState = updateState;
    return true;
}

void VehicleStateMachine::onPingTimeout()
{
    Notify("Narwhal_Current_State", "State="+QString::number(currentState).toStdString()+", id="+id.toStdString(), MOOSTime());
}

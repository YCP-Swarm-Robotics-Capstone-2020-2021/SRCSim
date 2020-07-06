/************************************************************/
/*    NAME: Kyle Leatherman                                              */
/*    ORGN: YCP                                             */
/*    FILE: MotionController.cpp                                        */
/*    DATE: 06/08/2020                                         */
/************************************************************/
#include <iterator>
#include "ivp/MBUtils.h"
#include "ivp/ACTable.h"
#include "MotionController.h"

using namespace std;

//---------------------------------------------------------
// Constructor

MotionController::MotionController()
{
    entryZone = new QLabel("Enter input");
}

//---------------------------------------------------------
// Destructor

MotionController::~MotionController()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool MotionController::OnNewMail(MOOSMSG_LIST &NewMail)
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

  if(key == "Current_Pos"){
    cout << "New Current Pos" << std::endl;
    handleCurrentPos(msg);

  }
  else if(key == "Current_State"){
      cout << "New_State" << std::endl;
      handleCurrentState(msg);
  }
  else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
    reportRunWarning("Unhandled Mail: " + key);
}

return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool MotionController::OnConnectToServer()
{
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool MotionController::Iterate()
{
AppCastingMOOSApp::Iterate();
// Do your thing here!
switch(state){
    case EnumDefs::VehicleStates::TELEOP:{
        QString moveData = "id="+ id +",Speed="+ QString::number(roboSpeed) + ",Curv=" + QString::number(roboCurv);
        Notify("Speed_Curv", moveData.toStdString(), MOOSTime());
        break;
    }
    case EnumDefs::VehicleStates::STANDBY:{
        QString moveData = "id="+ id +",Speed="+ QString::number(0) + ",Curv=" + QString::number(0);
        Notify("Speed_Curv", moveData.toStdString(), MOOSTime());
        break;
    }
    case EnumDefs::VehicleStates::ALLSTOP:{
        QString moveData = "id="+ id +",Speed="+ QString::number(0) + ",Curv=" + QString::number(0);
        Notify("Speed_Curv", moveData.toStdString(), MOOSTime());
        break;
    }
    default:{
        MOOSDebugWrite("MotionController: Invalid state");
        break;
    }
}



//AppCastingMOOSApp::PostReport();
return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool MotionController::OnStartUp()
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

void MotionController::registerVariables()
{
AppCastingMOOSApp::RegisterVariables();
Register("Current_State");
Register("Current_Pos");
}


//------------------------------------------------------------
// Procedure: buildReport()

bool MotionController::buildReport()
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

bool MotionController::handleCurrentPos(CMOOSMsg &msg){
     if(!msg.IsString()){
        return MOOSFail("You did not input a string you ninny");
     }
     double x = 0.0,y = 0.0;
     MOOSValFromString(x , msg.GetString(), "xPos");
     MOOSValFromString(y , msg.GetString(), "yPos");
     cout << "Coordinates are now "<< x <<" as x and "<< y <<" as y " << std::endl;


     return true;
}

bool MotionController::handleCurrentState(CMOOSMsg &msg){
     if(!msg.IsString()){
        return MOOSFail("You did not input a string you ninny");
     }
     int x;
     MOOSValFromString(x , msg.GetString(), "State");
     state = EnumDefs::VehicleStates(x);



     return true;
}

void MotionController::run(){
    Run(m_moosAppName,m_moosMissionFile);
}

void MotionController::startProcess(const std::string &sname, const std::string &moosfile, int argc, char **argv){

    SetCommandLineParameters(argc, argv);

    m_moosAppName = sname;
    m_moosMissionFile = moosfile;
    start();
}

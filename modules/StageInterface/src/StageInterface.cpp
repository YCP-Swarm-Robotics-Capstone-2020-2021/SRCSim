/************************************************************/
/*    NAME: Josiah Sam                                              */
/*    ORGN: YCP                                             */
/*    FILE: StageInterface.cpp                                        */
/*    DATE: 06/05/2020                                         */
/************************************************************/
#include <iterator>
#include "ivp/MBUtils.h"
#include "ivp/ACTable.h"
#include "StageInterface.h"
#include "global.h"

QList<double> StageManagerBuffer;
QList<double> StageInterfaceBuffer;

using namespace std;

//---------------------------------------------------------
// Constructor

StageInterface::StageInterface()
{
    manager = new StageManager();
}

//---------------------------------------------------------
// Destructor

StageInterface::~StageInterface()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool StageInterface::OnNewMail(MOOSMSG_LIST &NewMail)
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

  if(key == "FOO")
    cout << "great!";
  else if(key == "Speed_Curv"){
    OnSpeedCurv(msg);
  } else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
    reportRunWarning("Unhandled Mail: " + key);
}

return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool StageInterface::OnConnectToServer()
{
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool StageInterface::Iterate()
{
AppCastingMOOSApp::Iterate();
// Do your thing here!
AppCastingMOOSApp::PostReport();
return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool StageInterface::OnStartUp()
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
 if(param == "foo") {
   handled = true;
 }
 else if(param == "bar") {
   handled = true;
 } else if(param == "worldfile") {
    world_file = QString::fromStdString(value);
    handled = true;
    manager->setWorldFile(world_file);
 } else if(param == "numbots") {
    num_bots = QString::fromStdString(value).toInt();
    manager->setNumBots(num_bots);

    //initialize the map that will convert the identifier to the index of the robot
    for(int i = 0; i<num_bots; i++){
        index_map[ROBOT_IDENTIFIER+std::to_string(i)]=i;
    }

    //declare robot array
    handled = true;
 }if(!handled)
   reportUnhandledConfigWarning(orig);

}
manager->start();
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void StageInterface::registerVariables()
{
AppCastingMOOSApp::RegisterVariables();
    Register("Speed_Curv", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool StageInterface::buildReport()
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

bool StageInterface::OnSpeedCurv(CMOOSMsg &Msg)
{
    if(!Msg.IsString()){
        return MOOSFail("You did not input a string for the Speed_Curv message.");
    }
    double speed = 0.0, curv = 0.0;
    string id = "";
    int idx;
    if(!MOOSValFromString(speed, Msg.GetString(), "Speed")){
        return MOOSFail("Error getting speed out of Speed_Curv message.");
    } else if (!MOOSValFromString(curv, Msg.GetString(), "Curv")){
        return MOOSFail("Error getting Curv from Speed_Curv message.");
    } else if (!MOOSValFromString(id, Msg.GetString(), "id")){
        return MOOSFail("Error getting id from Speed_Curv message.");
    }
    idx = index_map[id];
    double forward_speed = 0.0;
    double turn_speed = 0.0;
    double side_speed = 0.0;
    if(speed >= 100.0){
        speed = 100.0;
    } else if (speed <= -100.0) {
        speed = -100.0;
    }
    speed = speed/100.0; //convert from percentage to
    forward_speed = speed*cos(curv*(PI/180.0));
    turn_speed    = (2*speed)*sin(curv*(PI/180.0));
    StageManagerBuffer.append(double(idx));
    StageManagerBuffer.append(forward_speed);
    StageManagerBuffer.append(side_speed);
    StageManagerBuffer.append(turn_speed);
    return true;
}
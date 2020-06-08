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

//QMutex StageManagerMutex;
//QSemaphore StageManagerSemFree(8);
//QSemaphore StageManagerSemAvail(0);
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
    cout<<"Outside OnSpeedCurv method."<<endl;
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
//AppCastingMOOSApp::PostReport();
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
    cout<<"World file = "<<world_file.toStdString()<<endl;
    handled = true;
    manager->setWorldFile(world_file);
 } else if(param == "numbots") {
    num_bots = QString::fromStdString(value).toInt();
    manager->setNumBots(num_bots);

    //initialize the map that will convert the identifier to the index of the robot
    for(int i = 0; i<num_bots; i++){
        index_map[ROBOT_IDENTIFIER+std::to_string(i)]=i;
        //cout<<"Identifier = "<<ROBOT_IDENTIFIER+std::to_string(i)           <<endl;
        //cout<<"Value = "     <<index_map[ROBOT_IDENTIFIER+std::to_string(i)]<<endl;
    }

    //declare robot array
    cout<<"Number of bots = "<<num_bots<<endl;
    handled = true;
 }if(!handled)
   reportUnhandledConfigWarning(orig);

}
//connect(this, setForwardSpeed(int, double), manager, manager->handleUpdateForwardSpeed(int, double));
//connect(this, setSideSpeed(int, double), manager, manager->handleUpdateSideSpeed(int, double));
//connect(this, setTurnSpeed(int, double), manager, manager->handleUpdateTurnSpeed(int, double));
manager->start();
/*connect(this, &StageInterface::hello, manager, &StageManager::helloWorld);
connect(this, &StageInterface::setForwardSpeed, manager, &StageManager::handleUpdateForwardSpeed, Qt::QueuedConnection);
connect(this, &StageInterface::setSideSpeed, manager, &StageManager::handleUpdateSideSpeed, Qt::QueuedConnection);
connect(this, &StageInterface::setTurnSpeed, manager, &StageManager::handleUpdateTurnSpeed, Qt::QueuedConnection);
*/
//connect(this, SIGNAL(setForwardSpeed(int, double)), manager, SLOT(handleUpdateForwardSpeed(int, double)), Qt::QueuedConnection);
//connect(this, SIGNAL(setSideSpeed(int, double)), manager, SLOT(handleUpdateSideSpeed(int, double)), Qt::QueuedConnection);
//connect(this, SIGNAL(setTurnSpeed(int, double)), manager, SLOT(handleUpdateTurnSpeed(int, double)), Qt::QueuedConnection);
registerVariables();
//emit hello();
return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void StageInterface::registerVariables()
{
AppCastingMOOSApp::RegisterVariables();
// Register("FOOBAR", 0);
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
    cout<<"Inside OnSpeedCurv method."<<endl;
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
    cout << "StageInterface: Speed = "<<speed<<". Curv = "<<curv<<"."<<endl;
    cout << "StageInterface: Forward_Speed = "<<forward_speed<<". Side_Speed = "<<side_speed<<". Turn_Speed = "<<turn_speed<<endl;
    //robots[idx].position->SetSpeed(forward_speed, side_speed, turn_speed);
    /*manager->getRobots()[idx].forward_speed = forward_speed;
    manager->getRobots()[idx].side_speed = side_speed;
    manager->getRobots()[idx].turn_speed = turn_speed;*/

    //emit setForwardSpeed(idx, forward_speed);
    //emit setSideSpeed(idx, side_speed);
    //emit setTurnSpeed(idx, turn_speed);

    /*manager->handleUpdateSideSpeed(idx, side_speed);
    manager->handleUpdateForwardSpeed(idx, forward_speed);
    manager->handleUpdateTurnSpeed(idx, turn_speed);*/

//    StageManagerSemFree.acquire();
  //  StageManagerMutex.lock();
    StageManagerBuffer.append(double(idx));
    StageManagerBuffer.append(forward_speed);
    StageManagerBuffer.append(side_speed);
    StageManagerBuffer.append(turn_speed);
    //StageManagerMutex.unlock();
    //StageManagerSemAvail.release();
    return true;
}

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


using namespace std;
QList<Robot> RobotList;

//---------------------------------------------------------
// Constructor

StageInterface::StageInterface(QObject * parent) : QObject(parent)
{
    //manager = new StageManager(this);
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
notifyCurrentPose();
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
    emit setWorldFile(world_file);
    //manager->setWorldFile(world_file);
 } else if(param == "numbots") {
    num_bots = QString::fromStdString(value).toInt();
    //manager->setNumBots(num_bots);
    emit setNumBots(num_bots);

    //initialize the map that will convert the identifier to the index of the robot
    for(int i = 0; i<num_bots; i++){
        index_map[ROBOT_IDENTIFIER+std::to_string(i)]=i;
    }

    //declare robot array
    handled = true;
 }if(!handled)
   reportUnhandledConfigWarning(orig);

}
//Q_ASSERT(QObject::connect(manager, SIGNAL(updatePose(int,double,double)), this, SLOT(notifyCurrentPose(int,double,double)), Qt::QueuedConnection));
//connect(manager, &StageManager::updatePose, this, &StageInterface::notifyCurrentPose);
//manager->start();
emit startStage();
registerVariables();
publishPose = true;
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
        return MOOSDebugWrite("Error getting speed out of Speed_Curv message.");
    } else if (!MOOSValFromString(curv, Msg.GetString(), "Curv")){
        return MOOSDebugWrite("Error getting Curv from Speed_Curv message.");
    } else if (!MOOSValFromString(id, Msg.GetString(), "id")){
        return MOOSDebugWrite("Error getting id from Speed_Curv message.");
    }
    idx = index_map[id];
    double forward_speed = 0.0;
    double turn_speed = 0.0;
    //double side_speed = 0.0;
    if(speed >= 100.0){
        speed = 100.0;
    } else if (speed <= -100.0) {
        speed = -100.0;
    }
    speed = speed/100.0; //convert from percentage to
    forward_speed = speed*cos(curv*(PI/180.0));
    turn_speed    = (2*speed)*sin(curv*(PI/180.0));
    emit setMotion(idx, forward_speed, turn_speed);
    return true;
}

void StageInterface::notifyCurrentPose()
{
    QString dataValue;
    for(int i = 0; i<num_bots; i++){
        if(publishPose && RobotList.length()>=num_bots){
            dataValue = "xPos="+QString::number(RobotList[i].xPos)+
                                ",yPos="+QString::number(RobotList[i].yPos)+
                                ",id=Dolphin"+QString::number(i);
        } else {
            dataValue = "xPos=0.0, yPos=0.0, id=Dolphin"+QString::number(i);
        }
        Notify("Update_Pos", dataValue.toStdString(), MOOSTime());
    }
}

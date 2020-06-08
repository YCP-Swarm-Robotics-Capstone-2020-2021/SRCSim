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

//---------------------------------------------------------
// Constructor

StageInterface::StageInterface()
{
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
 } else if(param == "numbots") {
    num_bots = QString::fromStdString(value).toInt();

    //initialize the map that will convert the identifier to the index of the robot
    for(int i = 0; i<num_bots; i++){
        index_map[ROBOT_IDENTIFIER+std::to_string(i)]=i;
        //cout<<"Identifier = "<<ROBOT_IDENTIFIER+std::to_string(i)           <<endl;
        //cout<<"Value = "     <<index_map[ROBOT_IDENTIFIER+std::to_string(i)]<<endl;
    }

    //declare robot array
    robots = new Robot[num_bots];
    cout<<"Number of bots = "<<num_bots<<endl;
    handled = true;
 }if(!handled)
   reportUnhandledConfigWarning(orig);

}
initialize();
registerVariables();
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
    string id = 0;
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
    forward_speed = speed*cos(curv);
    side_speed    = speed*sin(curv);
    robots[idx].position->SetSpeed(forward_speed, side_speed, turn_speed);
    cout << "StageInterface: Speed = "<<speed<<". Curv = "<<curv<<"."<<endl;
    cout << "StageInterface: Forward_Speed = "<<forward_speed<<". Side_Speed = "<<side_speed<<". Turn_Speed = "<<side_speed<<endl;
    return true;
}

void StageInterface::initialize()
{
    char arg1[world_file.toStdString().size()];
    char *arg[1];
    char **args[3];
    int y;
    for(int i = 0; i < (int)world_file.toStdString().size(); i++){
        arg1[i] = world_file.toStdString().c_str()[i];
        y = i;
    }
    arg1[y+1]= '\0';
    arg[0] = arg1;
    args[0] = arg;
    args[1] = arg;
    args[2] = NULL;
    int x = 2;
    Stg::Init(&x, args);
    world = new Stg::WorldGui(800, 700, "Stage Simulation");
    world->Load(world_file.toStdString());
    connect(world);
    world->Run();
    cout<<"Made it past."<<endl;
}

void StageInterface::connect(Stg::World *world)
{
  // connect the first population_size robots to this controller
  for (int idx = 0; idx < num_bots; idx++) {
    // the robots' models are named r0 .. r1999
    std::stringstream name;
    name << ROBOT_IDENTIFIER << idx;

    // get the robot's model and subscribe to it
    Stg::ModelPosition *posmod =
        reinterpret_cast<Stg::ModelPosition *>(world->GetModel(name.str()));
    assert(posmod != 0);

    robots[idx].position = posmod;
    robots[idx].position->Subscribe();
  }

  // register with the world
}


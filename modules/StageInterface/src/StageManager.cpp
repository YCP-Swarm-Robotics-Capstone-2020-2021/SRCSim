#include "StageManager.h"
    using namespace Stg;
    using namespace std;

StageManager::StageManager(QObject * parent) : QThread(parent)
{
    runStarted = false;

}

StageManager::~StageManager()
{

}

void StageManager::run()
{
    char arg1[world_file.toStdString().size()];
    char *arg[1];
    char **args[3];
    int y=0;
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
    printf("World file is: %s", world_file.toStdString().c_str());
    world->Load(world_file.toStdString());
    runStarted = true;
    stageRun = new StageRun(num_bots);
    stageRun->setNumBots(num_bots);
    stageRun->connectStage(world);
    world->Start();
    world->Run();
}

void StageRun::connectStage(World *world)
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

      robots[idx].position->SetSpeed(0.0, 0.0, 0.0);
      robots[idx].forward_speed = 0.0;
      robots[idx].side_speed = 0.0;
      robots[idx].turn_speed = 0.0;
      robots[idx].laser = dynamic_cast<ModelRanger *>(robots[idx].position->GetChild( name.str() ));
      robots[idx].laser->Subscribe();
    }

    // register with the world
    world->AddUpdateCallback(StageRun::Callback, reinterpret_cast<void *>(this));
}

void StageRun::Tick(World * world)
{
    if(world->paused){
        world->Start();
    }
    for (int idx = 0; idx < num_bots; idx++) {
      robots[idx].position->SetSpeed(robots[idx].forward_speed, robots[idx].side_speed, robots[idx].turn_speed);
      while(RobotList.length()<=idx){
          RobotList.append(Robot());
      }
      double x, y;
      x = robots[idx].position->GetPose().x;
      y = robots[idx].position->GetPose().y;
      RobotList[idx].xPos = x;
      RobotList[idx].yPos = y;
      RobotList[idx].attitude = robots[idx].position->GetPose().a*180.0/PI+180.0;
      RobotList[idx].current_speed = robots[idx].forward_speed;
      RobotList[idx].line_detected = (abs(x)>(BLACK_LINE_LOCATION/2.0-0.25) and abs(x)< (BLACK_LINE_LOCATION/2.0+0.25))
              or (abs(y)>(BLACK_LINE_LOCATION/2.0-0.25) and abs(y)< (BLACK_LINE_LOCATION/2.0+0.25));
      const std::vector<meters_t> &scan = robots[idx].laser->GetSensors()[0].ranges;
      uint32_t sample_count = scan.size();
      double minfrontdistance = 1.0;
      double backupdist = 0.3;
      double minleft = 1e6, minright = 1e6;
      bool obstruction = false;
      //bool backup = false;


      for (uint32_t i = 0; i < sample_count; i++) {

          if ((i > (sample_count / 3)) && (i < (sample_count - (sample_count / 3)))
              && scan[i] < minfrontdistance) {
            obstruction = true;
          }
          if (scan[i] < backupdist) {
            //backup = true;
          }
          if (i > sample_count / 2)
            minleft = std::min(minleft, scan[i]);
          else
            minright = std::min(minright, scan[i]);
      }
      if(obstruction){
          if(minleft > minright){
              RobotList[idx].sensorState = EnumDefs::RIGHT;
          }
          else if( minright > minleft){
              RobotList[idx].sensorState = EnumDefs::LEFT;
          }
          else{
              RobotList[idx].sensorState = EnumDefs::MIDDLE;
          }
      }
      else{
          RobotList[idx].sensorState = EnumDefs::NONE;
      }
    }
}

StageRun::StageRun(int num_bots)
{
    this->num_bots = num_bots;
    robots = new Robot[num_bots];
    for(int i = 0; i<num_bots; i++)
    {
        RobotList.append(robots[i]);
    }
}

StageRun::~StageRun()
{

}

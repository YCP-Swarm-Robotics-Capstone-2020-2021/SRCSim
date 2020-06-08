#include "StageManager.h"
#include "global.h"
    using namespace Stg;
    using namespace std;

StageManager::StageManager()
{

}

StageManager::~StageManager()
{

}

void StageManager::run()
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
    stageRun = new StageRun(num_bots);
    stageRun->setNumBots(num_bots);
    stageRun->connectStage(world);
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
    }

    // register with the world
    world->AddUpdateCallback(StageRun::Callback, reinterpret_cast<void *>(this));
}

void StageRun::Tick(World *)
{
    int index = 0;
    if(!StageManagerBuffer.isEmpty()){
        index = (int)StageManagerBuffer.takeFirst();
        robots[index].forward_speed = StageManagerBuffer.takeFirst();
        robots[index].side_speed = StageManagerBuffer.takeFirst();
        robots[index].turn_speed = StageManagerBuffer.takeFirst();
    }
    for (int idx = 0; idx < num_bots; idx++) {
      robots[idx].position->SetSpeed(robots[idx].forward_speed, robots[idx].side_speed, robots[idx].turn_speed);
    }
}

StageRun::StageRun(int num_bots){
    this->num_bots = num_bots;
    robots = new Robot[num_bots];
}

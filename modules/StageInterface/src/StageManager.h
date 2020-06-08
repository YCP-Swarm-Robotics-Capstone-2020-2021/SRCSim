#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <cmath>

#include "Stage-4.3/stage.hh"


#define ROBOT_IDENTIFIER "Dolphin"
class Robot {
public:
  Stg::ModelPosition *position;
  double forward_speed;
  double side_speed;
  double turn_speed;
};

using namespace Stg;

class StageRun
{
    StageRun(const StageRun &){}
public:
    StageRun(int num_bots);
    ~StageRun();
    void Tick(World *);
    void connectStage(World *world);
    void setNumBots(int bots){num_bots = bots;}
    static int Callback(World *world, void *userarg)
    {
      StageRun *stageRun = reinterpret_cast<StageRun*>(userarg);

      stageRun->Tick(world);

      // never remove this call-back
      return 0;
    }
protected:
protected:class Robot {
  public:
    Stg::ModelPosition *position;
    double forward_speed;
    double side_speed;
    double turn_speed;
  };

private:
    Robot *robots;
    int num_bots;

public slots:

    friend class StageManager;
};

class StageManager : public QThread
{
    Q_OBJECT
public:
    StageManager();

    ~StageManager();
    void run() override;

    void setWorldFile(QString file){world_file = file;}
    void setNumBots(int bots){num_bots = bots;}
    StageRun *stageRun;
protected:

private:
    Stg::WorldGui *world;
    QString world_file;
    int num_bots;

public slots:
    void handleUpdateForwardSpeed(int idx, double speed);
    void handleUpdateTurnSpeed(int idx, double speed);
    void handleUpdateSideSpeed(int idx, double speed);
    void helloWorld();
};
#endif // STAGEMANAGER_H

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
#include <thread>
#include <QTimer>
#include "global.h"


#define ROBOT_IDENTIFIER "Dolphin"

using namespace Stg;

class StageRun : public QObject
{
    Q_OBJECT
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

signals:
    void updatePose(int idx, double x, double y);
protected:

private:
    Robot *robots;
    int num_bots;
    QObject *parent;

public slots:

    friend class StageManager;
};

class StageManager : public QThread
{
    Q_OBJECT
public:
    StageManager(QObject * parent = nullptr);

    ~StageManager();
    void run() override;

    void setWorldFile(QString file){world_file = file;}
    void setNumBots(int bots){num_bots = bots;}
    StageRun *stageRun;
protected:
    bool runStarted;
public slots:
    void getNumBots(int bots){
        num_bots = bots;
    }
    void getWorldFile(QString world_file){
        this->world_file = world_file;
    }
    void getMotion(int idx, double xSpeed, double turnSpeed){
        if(runStarted){
            stageRun->robots[idx].forward_speed = xSpeed;
            stageRun->robots[idx].turn_speed = turnSpeed;
        }
    }
    void startManager(){
        this->start();
    }

private:
    Stg::WorldGui *world;
    QString world_file;
    int num_bots;
};
#endif // STAGEMANAGER_H

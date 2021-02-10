/************************************************************/
/*    NAME: Josiah Sam                                              */
/*    ORGN: YCP                                             */
/*    FILE: StageInterface.h                                          */
/*    DATE: 06/05/2020                                         */
/************************************************************/

#ifndef StageInterface_HEADER
#define StageInterface_HEADER

#include <QObject>
#include <iterator>
#include <MOOS/libMOOS/MOOSLib.h>
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <FL/Fl_Shared_Image.H>
#include <ivp/MBUtils.h>
#include <ivp/ACTable.h>
#include <QString>
#include <QThread>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sstream>
#include <iostream>
#include <cmath>
#include "StageManager.h"
#include "Stage-4.3/stage.hh"

class StageInterface : public QObject, public AppCastingMOOSApp
{
    Q_OBJECT
public:
  StageInterface(QObject *parent = nullptr);
  ~StageInterface();


 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload
   bool buildReport();
   bool OnSpeedCurv(CMOOSMsg &Msg);

 protected:
   void registerVariables();

private: // Configuration variables
    int num_bots;
    QString world_file;
    Stg::WorldGui *world;
    std::map<std::string, int> index_map;
    StageManager *manager;
    void notifyCurrentPose();
    bool publishPose;

public slots:
    //void notifyCurrentPose(int idx, double x, double y);

signals:
    void setNumBots(int bots);
    void setWorldFile(QString world_file);
    void setMotion(int idx, double xSpeed, double turnSpeed);
    void startStage();
};

#endif 

/************************************************************/
/*    NAME: Kyle Leatherman                                              */
/*    ORGN: YCP                                             */
/*    FILE: MotionController.h                                          */
/*    DATE: 06/08/2020                                         */
/************************************************************/

#ifndef MotionController_HEADER
#define MotionController_HEADER

#include <QObject>
#include <iterator>
#include <MOOS/libMOOS/MOOSLib.h>
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <ivp/MBUtils.h>
#include <ivp/ACTable.h>
#include <QString>
#include <QThread>
#include <QWidget>
#include <QKeyEvent>
#include <VehicleStateDefines.h>
#include <QLabel>
#include <string>
#include <iostream>
#include "zeta.h"
#include <stdlib.h>
#include <time.h>



class MotionController : public QThread, public AppCastingMOOSApp {
    Q_OBJECT
public:
  MotionController();
  ~MotionController();

  void startProcess(const std::string & , const std::string &, int argc, char * argv[]);



 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   bool handleCurrentPos(CMOOSMsg &msg);
   bool handleCurrentState(CMOOSMsg &msg);
   bool handleZetaInit(CMOOSMsg &msg);
   bool handleNeighborZeta(CMOOSMsg &msg);
   bool handleObjectDetected(CMOOSMsg &msg);


 protected: // Standard AppCastingMOOSApp function to overload
   bool buildReport();

   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);

 protected:
   void registerVariables();
   void run();
   void demoRun();
   void swarmRun();
   EnumDefs::VehicleStates swarmInit();
   QPointF linktoref();
   QList<double> toDoubleList(QList<QString>);
   double pointtoTraj(QPointF);
   void robotMover();
   void boundaryRecovery();
   void dodge();

 private: // Configuration variables
   double roboSpeed = 0;
   double roboCurv = 0;
   double x = 0;
   double y = 0;
   double boundary = 6.0;
   double attitude = 0;
   double max_speed = 100.0;
   double turn_speed = 15.0;
   double angle_tolerance = 10.0;
   EnumDefs::VehicleStates state = EnumDefs::STANDBY;
   QLabel *entryZone;
   QString id = "";
   std::string m_moosAppName,m_moosMissionFile;
   double xlinkoff = 0;
   double ylinkoff = 0;
   int linknum = 0;
   int numlinks = 0;
   QMap<QString,Zeta> *podmates;
   Zeta CurrentZeta;
   bool swarmflag = false;
   double kappa = 1.0;
   double dt = 1.0;
   QPointF goalpoint;
   double goalx, goaly;
   double goalangle;
   double posTolerance = 0.1;
   EnumDefs::SensorState dodgeState = EnumDefs::NONE;
   bool object = false;
   bool dodge_state_fwd = false;
   bool driving = false;
   bool done = false;
public slots:
   void setSpeed(double speed){roboSpeed = speed;}
   void setCurv(double curv){roboCurv = curv;}
   void dodgeStateFWD();

signals:

};

#endif 

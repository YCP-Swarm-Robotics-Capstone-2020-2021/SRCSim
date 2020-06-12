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

 protected: // Standard AppCastingMOOSApp function to overload
   bool buildReport();

   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);

 protected:
   void registerVariables();
   void run();


 private: // Configuration variables
   double roboSpeed = 0;
   double roboCurv = 0;
   VehicleStates state = VehicleStates::STANDBY;
   QLabel *entryZone;
   QString id = "";
   std::string m_moosAppName,m_moosMissionFile;

public slots:
   void setSpeed(double speed){roboSpeed = speed;}
   void setCurv(double curv){roboCurv = curv;}

signals:

public slots:
};

#endif 

/************************************************************/
/*    NAME: jsam                                              */
/*    ORGN: YCP                                             */
/*    FILE: SwarmHandler.h                                          */
/*    DATE: 07/23/2020                                         */
/************************************************************/

#ifndef SwarmHandler_HEADER
#define SwarmHandler_HEADER

#include <QObject>
#include <iterator>
#include <MOOS/libMOOS/MOOSLib.h>
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <ivp/MBUtils.h>
#include <ivp/ACTable.h>
#include <QString>
#include <QThread>
#include <VehicleStateDefines.h>
#include "zeta.h"

class Robot
{
public:
    Robot(EnumDefs::VehicleStates State){state=State; podMates=new QList<QString>();}
    QString id;
    EnumDefs::VehicleStates state;
    double xOffset;
    double yOffset;
    int linkageAssignment;
    QList<QString> *podMates;
    bool done = false;
};

class SwarmHandler : public QObject, public AppCastingMOOSApp
{
    Q_OBJECT
public:
  SwarmHandler();
  ~SwarmHandler();


 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload
   bool buildReport();
   bool onChangeState(CMOOSMsg & msg);
   void onRegistration(CMOOSMsg & msg);
   bool onCurrentState(CMOOSMsg & msg);
   bool checkState(EnumDefs::VehicleStates state);
   bool checkDone();
   QList<double> toDoubleList(QList<QString> input);
   void initializeSwarm();
   void incrementFormationZeta();

 protected:
   void registerVariables();

 private: // Configuration variables
    EnumDefs::VehicleStates state;
    QMap<QString, Robot*> *registration;
    Zeta *zetaControl;
    bool SwarmInitialized = false;
    QList<QString> m_neighbors;
    QString currentShape = "none";
    double xIncrement = 0.0;
    double yIncrement = 0.0;
    double rotationIncrement = 0.0;
    bool inRun = false;
    double m_first_time = 0.0;
    double m_move_delay = 0.0;
    bool m_move_formation = false;
signals:

public slots:
};

#endif 

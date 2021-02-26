/************************************************************/
/*    NAME: Josiah Sam                                              */
/*    ORGN: YCP                                             */
/*    FILE: VehicleStateMachine.h                                          */
/*    DATE: 06/08/2020                                         */
/************************************************************/

#ifndef VehicleStateMachine_HEADER
#define VehicleStateMachine_HEADER

#include <QObject>
#include <iterator>
#include <MOOS/libMOOS/MOOSLib.h>
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <ivp/MBUtils.h>
#include <ivp/ACTable.h>
#include <QString>
#include <QThread>
#include "VehicleStateDefines.h"
#include <QMap>
#include <QTimer>

class VehicleStateMachine : public QObject, public AppCastingMOOSApp
{
    Q_OBJECT
public:
  VehicleStateMachine();
  ~VehicleStateMachine();


 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload
   bool buildReport();

 protected:
   void registerVariables();
   bool onChangeState(CMOOSMsg &Msg);

 private: // Configuration variables
   EnumDefs::VehicleStates currentState;
   EnumDefs::VehicleStates m_previousState;
   QString id;
   bool registered = false;
   double timeout;
   int count;
   bool dodgeon = false;


   bool m_previousBoundaryState = false;
   bool m_currentBoundaryState = false;
signals:

public slots:
   void onPingTimeout();

};

#endif 

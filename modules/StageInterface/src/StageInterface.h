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
#include <ivp/MBUtils.h>
#include <ivp/ACTable.h>
#include <QString>
#include <QThread>


class StageInterface : public QObject, public AppCastingMOOSApp
{
    Q_OBJECT
public:
  StageInterface();
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

signals:

public slots:
};

#endif 

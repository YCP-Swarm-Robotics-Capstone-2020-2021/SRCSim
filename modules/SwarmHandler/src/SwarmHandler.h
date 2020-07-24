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

 protected:
   void registerVariables();

 private: // Configuration variables

signals:

public slots:
};

#endif 

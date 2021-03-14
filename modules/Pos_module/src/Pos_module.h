/************************************************************/
/*    NAME: Kyle Leatherman                                              */
/*    ORGN: YCP                                             */
/*    FILE: Pos_module.h                                          */
/*    DATE: 06/05/2020                                         */
/************************************************************/

#ifndef Pos_module_HEADER
#define Pos_module_HEADER

#include <QObject>
#include <iterator>
#include <MOOS/libMOOS/MOOSLib.h>
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <ivp/MBUtils.h>
#include <ivp/ACTable.h>
#include <QString>
#include <QThread>


class Pos_module : public QObject, public AppCastingMOOSApp
{
    Q_OBJECT
public:
  Pos_module();
  ~Pos_module();


 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   bool handleUpdatePos(CMOOSMsg &msg);

 protected: // Standard AppCastingMOOSApp function to overload
   bool buildReport();

 protected:
   void registerVariables();
   void detectBoundary();

 private: // Configuration variables
   double x, y, attitude;
   QString id = "";
   double m_boundaryWidth = 6;
   double m_boundaryHeight = 6;
   bool m_boundary_detected = false;

signals:

public slots:
};

#endif 

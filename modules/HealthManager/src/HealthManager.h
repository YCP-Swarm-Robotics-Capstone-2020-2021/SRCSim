/************************************************************/
/*    NAME: Kyle Leatherman                                              */
/*    ORGN: YCP                                             */
/*    FILE: HealthManager.h                                          */
/*    DATE: 11/07/2020                                         */
/************************************************************/

#ifndef HealthManager_HEADER
#define HealthManager_HEADER

#include <QObject>
#include <iterator>
#include <MOOS/libMOOS/MOOSLib.h>
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <MOOS/libMOOS/Utils/ConsoleColours.h>
#include <ivp/MBUtils.h>
#include <ivp/ACTable.h>
#include <QString>
#include <QThread>
#include <VehicleStateDefines.h>



class HealthManager : public QObject, public AppCastingMOOSApp
{
    Q_OBJECT
public:
  HealthManager(std::string sName, std::string sMissionFile);
  ~HealthManager();


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
   bool RunInQtEventLoop(const std::string & sName, const std::string & sMissionFile);
   bool doMOOSWork();
   void restartProcess(QList<QString> appName);

    QTimer iterateTimer;
    virtual bool OnIteratePrepare() final
    {
      m_dfFreq = currentFrequency; //Store the value back in so that we don't have to worry about other dependencies.
      return true;
    }
    double currentFrequency;
    std::string m_moosAppName,m_moosMissionFile;
    QString m_binarypath;
    double m_launchtime;
    bool m_runSim;
    bool m_launchmode = false;
    std::string m_substring;

signals:
   void workFinished();

public slots:
    void run();
};

#endif 

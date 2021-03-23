/************************************************************/
/*    NAME: Josiah Sam                                              */
/*    ORGN: YCP                                             */
/*    FILE: CameraInterface.h                                          */
/*    DATE: 03/23/2021                                         */
/************************************************************/

#ifndef CameraInterface_HEADER
#define CameraInterface_HEADER

#include <QObject>
#include <iterator>
#include <MOOS/libMOOS/MOOSLib.h>
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <MOOS/libMOOS/Utils/ConsoleColours.h>
#include <ivp/MBUtils.h>
#include <ivp/ACTable.h>
#include <QTimer>
#include <QString>
#include <QThread>


class CameraInterface : public QObject, public AppCastingMOOSApp
{
    Q_OBJECT
public:
  CameraInterface(std::string sName, std::string sMissionFile);
  ~CameraInterface();

  void startProcess(const std::string &, const std::string &, int argc, char * argv[]);

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

    virtual bool OnIteratePrepare() final
    {
      m_dfFreq = currentFrequency; //Store the value back in so that we don't have to worry about other dependencies.
      return true;
    }

    std::string m_moosAppName,m_moosMissionFile;

    QTimer iterateTimer;
    double currentFrequency;

signals:
    void workFinished();

public slots:
   void run();

  private:
    bool onStartupComplete = false;
};

#endif 

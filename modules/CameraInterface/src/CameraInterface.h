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
#include <QUdpSocket>
#include <QJsonObject>
#define debug 1
static const int READ_DATA_PERIOD = 1000; //msec
struct Position{
  double x;
  double y;
  double theta;
};

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
    QUdpSocket m_udp_socket;
    QMap<QString, Position> m_id_to_posiion_map;
    QTimer m_read_data_timer;
#if debug == 1
    QStringList debug_string = {"{\"messageNum\":0,\"data\":{\"robots\":[{\"id\": \"dolphin0\", \"pos\": [5.5,7.6], \"ort\": 95.6},{\"id\": \"dolphin1\", \"pos\": [9.1,-1.3], \"ort\": 185.3},{\"id\": \"dolphin3\", \"pos\": [-3.8,8.6], \"ort\": 52.1}]}}",
                                "{\"messageNum\":1,\"data\":{\"robots\":[{\"id\": \"dolphin0\", \"pos\": [6.0,7.6], \"ort\": 95.6},{\"id\": \"dolphin1\", \"pos\": [9.1,-2.3], \"ort\": 180.3},{\"id\": \"dolphin3\", \"pos\": [-3.8,8.6], \"ort\": 62.1}]}}",
                                "{\"messageNum\":2,\"data\":{\"robots\":[{\"id\": \"dolphin0\", \"pos\": [6.5,7.6], \"ort\": 95.6},{\"id\": \"dolphin1\", \"pos\": [9.1,-3.3], \"ort\": 170.3},{\"id\": \"dolphin3\", \"pos\": [-3.8,8.6], \"ort\": 72.1}]}}",
                                "{\"messageNum\":3,\"data\":{\"robots\":[{\"id\": \"dolphin0\", \"pos\": [7.0,7.6], \"ort\": 95.6},{\"id\": \"dolphin1\", \"pos\": [9.1,-4.3], \"ort\": 165.3},{\"id\": \"dolphin3\", \"pos\": [-3.8,8.6], \"ort\": 82.1}]}}",
                                "{\"messageNum\":4,\"data\":{\"robots\":[{\"id\": \"dolphin0\", \"pos\": [7.5,7.6], \"ort\": 95.6},{\"id\": \"dolphin1\", \"pos\": [8.1,-1.3], \"ort\": 155.3},{\"id\": \"dolphin3\", \"pos\": [-3.8,8.6], \"ort\": 92.1}]}}",
                                "{\"messageNum\":5,\"data\":{\"robots\":[{\"id\": \"dolphin0\", \"pos\": [8.0,7.6], \"ort\": 95.6},{\"id\": \"dolphin1\", \"pos\": [7.1,-1.3], \"ort\": 145.3},{\"id\": \"dolphin3\", \"pos\": [-3.8,8.6], \"ort\": 82.1}]}}",
                                "{\"messageNum\":6,\"data\":{\"robots\":[{\"id\": \"dolphin0\", \"pos\": [8.5,7.6], \"ort\": 95.6},{\"id\": \"dolphin1\", \"pos\": [6.1,-1.3], \"ort\": 135.3},{\"id\": \"dolphin3\", \"pos\": [-3.8,8.6], \"ort\": 72.1}]}}",
                                "{\"messageNum\":7,\"data\":{\"robots\":[{\"id\": \"dolphin0\", \"pos\": [9.0,7.6], \"ort\": 95.6},{\"id\": \"dolphin1\", \"pos\": [5.1,-1.3], \"ort\": 125.3},{\"id\": \"dolphin3\", \"pos\": [-3.8,8.6], \"ort\": 62.1}]}}"
                               };
#endif

signals:
    void workFinished();

public slots:
   void run();
   void readData();
   void processData(QString datagram);

  private:
    bool onStartupComplete = false;
};

#endif 

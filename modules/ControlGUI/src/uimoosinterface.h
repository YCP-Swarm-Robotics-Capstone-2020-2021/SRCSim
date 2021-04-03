#ifndef UIMOOSINTERFACE_H
#define UIMOOSINTERFACE_H

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

static const int BOUNDARY_SIZE_UPDATE_INTERVAL = 1;
static const std::string SPEED_CMD = "Speed_Curv";
static const std::string RUN_STARTED = "RUN_STARTED";
static const std::string RUN_ENDED = "RUN_ENDED";
static const std::string PING="GCS_CONNECTION";
static const int pingTimerSetting = 3;

class UIMoosInterface : public QObject, public AppCastingMOOSApp
{
    Q_OBJECT
public:
    UIMoosInterface(std::string sName, std::string sMissionFile);
    ~UIMoosInterface();

    void startProcess(const std::string &, const std::string &, int argc, char * argv[]);


protected: // Standard MOOSApp functions to overload
    bool OnNewMail(MOOSMSG_LIST &NewMail);
    bool Iterate();
    bool OnConnectToServer();
    bool OnStartUp();

protected: // Standard AppCastingMOOSApp function to overload
    bool buildReport();
    void registerVariables();

public slots:
    void run();
    void receiveZeta(QString);
    void receiveStateCMD(EnumDefs::VehicleStates, QString, int, int, double, int);
    void receiveSpeed(QString id, bool forward, bool reverse, bool left, bool right, int speed);
    void sendLogBookmark();
    void updateBoundarySize(int width, int height);
    void onRunStarted(std::string msg);
    void onRunEnded(std::string msg);
    void checkActive();
    void send_ping();

signals:
    void workFinished();
    void regIn(QList<QString>);
    void updateState(QString,int);
    void updateProcessWatch(QString id, QString msg);
    void updateWarning(QString id, QString msg, int);
    void updateDolphinVersion(QString id, QString version, QString msg);

private: // Configuration variables
    bool RunInQtEventLoop(const std::string & sName, const std::string & sMissionFile);
    bool doMOOSWork();

    virtual bool OnIteratePrepare() final
    {
      m_dfFreq = currentFrequency; //Store the value back in so that we don't have to worry about other dependencies.
      return true;
    }


    std::string m_moosAppName,m_moosMissionFile;

    QTimer pingTimer;
    QTimer iterateTimer;
    QTimer callcheckactive;
    double currentFrequency;
    int m_logBookmarkCounter=0;
    QList<QString> m_idList;
    EnumDefs defs;
    int m_boundary_width = 6;
    int m_boundary_height = 6;
    int m_publishBoundarySizeCounter = 0;
    double m_timeout;
    double m_lastupdated = 0;
    QMap<QString , QPair<double , bool> > m_updatemap;
};

#endif // UIMOOSINTERFACE_H

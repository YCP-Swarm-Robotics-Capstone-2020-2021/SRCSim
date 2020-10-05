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

signals:
    void workFinished();
    void regIn(QList<QString>);
    void updateState(QString,int);

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
    QList<QString> m_idList;
};

#endif // UIMOOSINTERFACE_H

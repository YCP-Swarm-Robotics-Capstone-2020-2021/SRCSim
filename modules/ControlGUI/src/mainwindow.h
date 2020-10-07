#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMap>
#include <QList>
#include "VehicleStateDefines.h"
#include "swarmformationpainter.h"

#define SPEED_INTERVAL 5

class RobotState {
    public:
    RobotState(){
        batteryCharge = 100;
        maxSpeed = 100;
        cmdSpeed = 0;
        status = EnumDefs::NORMAL;
        state = EnumDefs::STANDBY;
        for(int j = 0; j<4; j++){
            motorSpeed[j] = 0;
            motorCurrent[j] = 0;
        }
    }
    ~RobotState(){}

        double batteryCharge;
        int maxSpeed;

        int cmdSpeed;

        EnumDefs::StatusState status;
        EnumDefs::VehicleStates state;
        QString id;
        double motorCurrent[4];
        double motorSpeed[4];
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    EnumDefs defs;
    EnumDefs::VehicleStates m_currentState;
    QString m_currentBotID;
    int m_numBots;
    int m_maxSpeed;

    QMap<QString, RobotState> m_robotStateMap;
    QMap<QString, QList<QString>> m_robot_message_buffer;

    SwarmFormationPainter *myPainter;

    bool startup = true;
public slots:
    void setBotList(QList<QString> list);
    void setupStateSelection();
    void setupShapeList();

    void onSubmitStateButtonClicked();
    void onCurrentBotChanged(QString bot);
    void onCurrentStateChanged(QString state);
    void onKillAllPressed();

    void updateDebugText(QString);
    void updateWarningText(QString);
    void updateMotorSpeed(double speed, int motor, QString dolphin);
    void updateMotorCurrent(double current, int motor, QString dolphin);
    void updateBatteryPerc(double, QString);
    void updateDolphinStatus(EnumDefs::StatusState, QString);
    void updateDolphinState(QString, int);
    void onMaxSpeedChanged(int speed){m_maxSpeed = speed;}

    void onForwardButtonPressed();
    void onBackwardButtonPressed();
    void onLeftButtonPressed();
    void onRightButtonPressed();
    void onSpeedUpButtonPressed();
    void onSlowDownButtonPressed();
    void onBrakeButtonPressed();
    void updateCurrentDisplay();

    void printWarning(QString text, QString dolphin);
    void printCaution(QString text, QString dolphin);
    void printAdvisory(QString text, QString dolphin);
    void printText(QString text, QString dolphin);

    //Swarm Page Methods
    void onPreveiwPressed();
signals:
    void sendStateCMD(EnumDefs::VehicleStates, QString, int);
    void updatePaintList(QList<QString> list);
};

#endif // MAINWINDOW_H

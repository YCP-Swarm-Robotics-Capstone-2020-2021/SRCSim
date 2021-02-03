#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMap>
#include <QList>
#include "VehicleStateDefines.h"
#include "swarmformationpainter.h"
#include <QShortcut>

#define BUTTON_PRESS_INTERVAL 200
#define SPEED_INTERVAL 5

class RobotState {
    public:
        RobotState(){
            batteryCharge = 100;
            maxSpeed = 100;
            cmdSpeed = 50;
            status = EnumDefs::NORMAL;
            state = EnumDefs::STANDBY;
            for(int j = 0; j<4; j++){
                motorSpeed[j] = 0;
                motorCurrent[j] = 0;
            }
        }
        ~RobotState(){}

    public:
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
    QMap<QString, QString> m_robotProcessMap;
    QMap<QString, QList<QString>> m_robot_message_buffer;

    SwarmFormationPainter *myPainter;

    bool startup = true;

    QTimer forwardTimer;
    QTimer backTimer;
    QTimer leftTimer;
    QTimer rightTimer;

    bool forward = false;
    bool reverse = false;
    bool right = false;
    bool left = false;

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
    void updateDolphinWatch(QString, QString);
    void updateDolphinMsg(QString id, QString msg, int lvl);
    void onMaxSpeedChanged(int speed){m_maxSpeed = speed;}

    void onForwardButtonPressed();
    void onBackwardButtonPressed();
    void onLeftButtonPressed();
    void onRightButtonPressed();
    void onForwardButtonReleased();
    void onReverseButtonReleased();
    void onLeftButtonReleased();
    void onRightButtonReleased();


    void onSpeedUpButtonPressed();
    void onSlowDownButtonPressed();
    void onBrakeButtonPressed();
    void updateCurrentDisplay();

    void printWarning(QString text, QString dolphin);
    void printCaution(QString text, QString dolphin);
    void printAdvisory(QString text, QString dolphin);
    void printText(QString text, QString dolphin);

    //Swarm Page Methods
    void descretizeZoom(int);
    void onPreveiwPressed();
signals:
    void sendStateCMD(EnumDefs::VehicleStates, QString, int);
    void sendSpeed(QString id, bool forward, bool reverse, bool left, bool right, int speed);
    void updatePaintList(QList<QString> list);
    void zoomValue(int);
    void zetaSent(QString);
    void logBookmarkReq();
};

#endif // MAINWINDOW_H

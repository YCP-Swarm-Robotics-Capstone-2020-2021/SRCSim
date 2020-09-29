#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "VehicleStateDefines.h"

#define SPEED_INTERVAL 5

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

public slots:
    void setBotList(QList<QString> list);
    void onSubmitStateButtonClicked();
    void onCurrentBotChanged(QString bot);
    void onCurrentStateChanged(QString state);
    void updateDebugText(QString);
    void updateMotorSpeed(double speed, int motor);
    void updateMotorCurrent(double current, int motor);
    void updateBatteryPerc(double);
    void onMaxSpeedChanged(int speed){m_maxSpeed = speed;}

    void onForwardButtonPressed();
    void onBackwardButtonPressed();
    void onLeftButtonPressed();
    void onRightButtonPressed();
    void onSpeedUpButtonPressed();
    void onSlowDownButtonPressed();
    void onBrakeButtonPressed();

signals:
    void sendStateCMD(EnumDefs::VehicleStates, QString, int);
};

#endif // MAINWINDOW_H

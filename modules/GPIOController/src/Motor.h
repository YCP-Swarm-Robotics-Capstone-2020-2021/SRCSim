#ifndef MOTOR_H
#define MOTOR_H

#define PI 3.141592653589

#include <QObject>
#include <QTimer>
#include <pigpio.h>

const static std::string MOTOR_CURRENT_SPEED = "MOTOR_CURRENT_SPEED";
enum SIDE{
    LEFT,
    RIGHT
};

class Motor : public QObject
{
    Q_OBJECT
public:
    explicit Motor(QObject *parent = nullptr);

    int readGPIO;
    int writeGPIO;
    int maxRPM;
    int id;
    int cwhigh;
    int cwlow;
    int ccwhigh;
    int ccwlow;
    int dbhigh;
    int dblow;
    double rdhigh;
    double rdlow;
    bool reversed;
    int p;
    double i;
    double d;
    double wheelrad;
    double cmdSpeed = 0;
    double cmdRPM = 0;
    double currentSpeed;
    double currentRPM;
    SIDE side;

    QTimer notifyCurrentSpeedTimer;
public slots:
    void notifyCurrentSpeed();
    void updateCmdSpeed(double speed);
signals:
    void notifyMOOSMsg(QString key, QString msg);
};

#endif // MOTOR_H

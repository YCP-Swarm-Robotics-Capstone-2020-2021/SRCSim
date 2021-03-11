#include "Motor.h"

Motor::Motor(QObject *parent) : QObject(parent)
{
        readGPIO = 0;
        writeGPIO = 0;
        maxRPM = 0;
        id = 0;
        cwhigh = 0;
        cwlow = 0;
        ccwhigh = 0;
        ccwlow = 0;
        dbhigh = 0;
        dblow = 0;
        rdhigh = 0;
        rdlow = 0;
        reversed = 0;
        p = 0;
        i = 0;
        d = 0;
        wheelrad = 0;
        side = SIDE::LEFT;
        connect(&notifyCurrentSpeedTimer,&QTimer::timeout,this, &Motor::notifyCurrentSpeed);
}

void Motor::notifyCurrentSpeed()
{
    QString key = QString::fromStdString(MOTOR_CURRENT_SPEED);
    QString msg = "Speed="+QString::number(currentSpeed)+", MotorID="+QString::number(id);
    emit notifyMOOSMsg(key, msg);
}

void Motor::updateCmdSpeed(double speed)
{
    if(reversed){
        speed = -speed;
    }
    cmdSpeed = speed;
    if(cmdSpeed > 0){ //CCW

    } else if (cmdSpeed < 0) { //CW

    } else { //stationary

    }
}

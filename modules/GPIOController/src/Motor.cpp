#include "Motor.h"
#include <iostream>
using namespace std;

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
        connect(&cmdMotorTimer,&QTimer::timeout,this, &Motor::publishCMDPulseWidth);

}

Motor::~Motor()
{
    gpioTerminate();
}
void Motor::notifyCurrentSpeed()
{
    QString key = QString::fromStdString(MOTOR_CURRENT_SPEED);
    QString msg = "Speed="+QString::number(currentSpeed)+", MotorID="+QString::number(id);
    emit notifyMOOSMsg(key, msg);
}

void Motor::updateCmdSpeed(double speed)
{
    //speed is in feet/sec.
    if(reversed){
        speed = -speed;
    }
    cmdSpeed = speed;
    cmdRPM = fps_to_rpm(cmdSpeed);
    if(cmdSpeed > 0){ //CCW
        double range = abs(ccwhigh-ccwlow);
        double ratio = range *(cmdRPM/maxRPM);
        cmdPulseWidth = ratio + ccwlow;
    } else if (cmdSpeed < 0) { //CW
        double range = abs(cwhigh-cwlow);
        double ratio = range *(cmdRPM/maxRPM);
        cmdPulseWidth = cwlow+ratio;
    } else { //stationary
        double range = abs(dbhigh-dblow);
        cmdPulseWidth = dblow+range/2.0;
    }
}

double  Motor::fps_to_rpm(double fps)
{
    double angular_velocity = fps/(wheelrad);
    return angular_velocity*(60.0/2*PI);
}

double Motor::rpm_to_fps(double rpm)
{
    double angular_velocity = rpm*(2*PI/60.0);
    return angular_velocity*wheelrad;
}

void Motor::startUp()
{
    //DO WORK TO SETUP GPIOs and CALLBACK HERE
    int ret = gpioInitialise();
    if(ret < 0){return;}
    pigpio_daemon = ret;
    gpioSetMode(readGPIO, PI_INPUT);
    gpioSetMode(writeGPIO, PI_OUTPUT);
    gpioSetPWMrange(writeGPIO, PWM_WRITE_RANGE);
    gpioSetPWMfrequency(writeGPIO, 50);
    cmdMotorTimer.start(motor_control_period);
}

void Motor::publishCMDPulseWidth()
{
    //TODO: Do work to publish PWM signal here
  cout<<"We are attempting to control the motor: "<<id<<". Frequency is: "<<cmdPulseWidth<<". CMDSpeed: "<<cmdSpeed<<". cmdRPM: "<<cmdRPM<<endl;
  gpioHardwarePWM(writeGPIO, 50, cmdPulseWidth*50);
}

void Motor::readPulseWidth(int gpio, int level, uint32_t tick)
{
  cout<<gpio<<" "<<level<<" "<<tick<<endl;
}

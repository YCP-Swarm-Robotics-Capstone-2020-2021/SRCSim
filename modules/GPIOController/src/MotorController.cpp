#include "MotorController.h"

MotorController::MotorController(QObject *parent) : QObject(parent)
{
    for(int i =0; i<2; i++){
        QList<Motor*> motorList;
        motorList.append(new Motor(this));
        motorList.append(new Motor(this));
        motorMap.insert(SIDE(i),  motorList );
    }
    for(auto list : motorMap){
        for(auto motor : list){
            connect(motor, &Motor::notifyMOOSMsg,this,&MotorController::notifyMOOSMsg);
        }
    }
}

void MotorController::setupDeadbandRange(int h, int l)
{
    for(auto list : motorMap){
        for(auto item : list){
            item->dblow = l;
            item->dbhigh = h;
        }
    }
}

void MotorController::start()
{
    for(auto list : motorMap){
        for(auto motor : list){
            motor->notifyCurrentSpeedTimer.start(notifyCurrentSpeedInterval*MS_TO_S);
	    motor->startUp();
        }
    }
}

void MotorController::onSpeedCurv(double speed, double curv, bool fromOverride)
{
    bool processMsg = false;
    if(override){
        if(fromOverride){
            processMsg = true;
        }
    }
    else {
        processMsg = true;
    }
    if(!processMsg){
        return;
    }
    //clamp the speed
    speed = qBound(-100.0, speed, 100.0);
    //convert from a percentage
    speed = speed/100.0;
    double forward_speed = speed*cos(curv*(PI/180.0));
    double turn_speed    = (speed)*sin(curv*(PI/180.0));

    double right_speed = qBound(-1.0,forward_speed + turn_speed,1.0)*maxSpeed;
    double left_speed = qBound(-1.0,forward_speed - turn_speed, 1.0)*maxSpeed;

    for(auto motor : motorMap[LEFT]){
        motor->updateCmdSpeed(left_speed);
    }
    for(auto motor : motorMap[RIGHT]){
        motor->updateCmdSpeed(right_speed);
    }
}

void MotorController::onSpeedCurvOverride(double speed, double curv)
{
    onSpeedCurv(speed, curv, true);
}

#include "MotorController.h"

MotorController::MotorController(QObject *parent) : QObject(parent)
{
    QList<Motor*> motorList;
    for(int i =0; i<2; i++){
        motorList.append(new Motor(this));
        motorList.append(new Motor(this));
        motorMap.insert(SIDE(i),  motorList );
    }
}

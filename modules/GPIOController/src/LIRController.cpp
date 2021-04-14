#include "LIRController.h"
#include <iostream>
#include "pigpiod_if2.h"

using namespace std;
LIRController::LIRController(QObject *parent) : QObject(parent)
{

}

bool LIRController::start()
{
    int ret = pigpio_start(NULL,NULL);
    if(ret < 0){
      std::cout<<"ERROR in LIRController: COULD NOT CONNECT TO PIGPIOD DAEMON"<<std::endl;
        return false;
    }
    pigpio_daemon = ret;
    Init_Pigpiod(pigpio_daemon, sensor_list[LEFT].bus, sensor_list[RIGHT].bus, address);
    if(!sensor_list[LEFT].setupComplete){
        sensor_list[LEFT].setup();
    }
    if(!sensor_list[RIGHT].setupComplete){
        sensor_list[RIGHT].setup();
    }
    return sensor_list[LEFT].setupComplete && sensor_list[RIGHT].setupComplete;
}

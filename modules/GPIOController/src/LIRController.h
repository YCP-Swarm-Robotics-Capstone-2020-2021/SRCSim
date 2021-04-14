#ifndef LIRCONTROLLER_H
#define LIRCONTROLLER_H

#include <QObject>


extern "C"{
    #include "VL53L1X_api.h"
    #include "vl53l1_platform.h"
    #include "vl53l1_types.h"
    #include "vl53l1_error_codes.h"
}
#include "VehicleStateDefines.h"
#include <iostream>

#define LEFT 0
#define RIGHT 1

class LIRSensor
{
public:
    double frequency;
    double distance;
    int intGpio;
    int side;
    int bus;
    bool setupComplete = false;

    void setup(){
        VL53L1X_ERROR status = VL53L1_ERROR_NONE;
        uint8_t bootState = 0;
        status = VL53L1X_BootState(bus, &bootState);
        if(!bootState){
            std::cout<<"IR Sensor not yet booted."<<std::endl;
            return;
        }
        status = VL53L1X_SensorInit(bus);
        if(status != VL53L1_ERROR_NONE){
            std::cout<<"Error Initializing Sensor"<<std::endl;
            return;
        }
        status = VL53L1X_StartRanging(bus);
        if(status != VL53L1_ERROR_NONE){
            std::cout<<"Error starting the ranging functionality."<<std::endl;
            return;
        }
        setupComplete = true;
    }
};

class LIRController : public QObject
{
    Q_OBJECT
public:
    explicit LIRController(QObject *parent = nullptr);
    bool start();
    int pigpio_daemon;
    int address = 0x52;
    QMap<int, LIRSensor> sensor_list;

signals:

};

#endif // LIRCONTROLLER_H

#ifndef LIRCONTROLLER_H
#define LIRCONTROLLER_H

#include <QObject>
#include <QTimer>

extern "C"{
    #include "VL53L1X_api.h"
    #include "vl53l1_platform.h"
    #include "vl53l1_types.h"
    #include "vl53l1_error_codes.h"
}
#include "VehicleStateDefines.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "pigpiod_if2.h"

#define LEFTSENSOR 0
#define RIGHTSENSOR 1

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
	uint16_t id;
	status = VL53L1X_GetSensorId(bus, &id);
	if(status != VL53L1_ERROR_NONE){
	  std::cout<<"ERROR in getting ID "<<QString::number(status).toStdString()<<std::endl;
	  std::cout<<"Error getting IR Sensor ID for bus "<<bus<<std::endl;
	  return;
	}
	if(id == 0xEACC){
	  std::cout<<"IR Sensor ID is 0xEACC for bus "<<bus<<std::endl;
	}
	else {
	  std::cout<<"IR Sensor ID is "<<QString::number(id).toStdString()<<" for bus "<<bus<<std::endl;
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
	/*uint8_t dataReady = 0;
	while(true){
	while(dataReady==0){
	  std::this_thread::sleep_for(std::chrono::milliseconds(50));
	  status = VL53L1X_CheckForDataReady(bus, &dataReady);
	  if(status != VL53L1_ERROR_NONE){
            std::cout<<"Error starting the ranging functionality."<<std::endl;
            return;
          }
	}

	dataReady = 0;
	uint16_t distance;
        status = VL53L1X_GetDistance(bus, &distance);
	std::cout<<"Distance = "<<QString::number(distance).toStdString()<<std::endl;
	}*/
    }

    double getRangeData()
    {
        VL53L1X_ERROR status = VL53L1_ERROR_NONE;
        uint8_t dataReady = 0;
	while(dataReady==0){
	  std::this_thread::sleep_for(std::chrono::milliseconds(50));
	  status = VL53L1X_CheckForDataReady(bus, &dataReady);
	  if(status != VL53L1_ERROR_NONE){
            std::cout<<"Error starting the ranging functionality."<<std::endl;
            return -1;
          }
	}
	uint16_t distance;
        status = VL53L1X_GetDistance(bus, &distance);
	return distance;
    }
};

const static std::string OBJECT_MSG = "OBJECT_DETECTED";

class LIRController : public QObject
{
    Q_OBJECT
public:
    explicit LIRController(QObject *parent = nullptr);
    ~LIRController(){
      Close_Pigpiod();
      pigpio_stop(pigpio_daemon);
      std::cout<<"Disconnecting from daemon."<<std::endl;
    }
    bool start();
    int pigpio_daemon;
    int address = 0x52;
    QMap<int, LIRSensor> sensor_list;
    double minRangeMM = 100;
    public slots:
      void getRanges();
 signals:
    void notifyMOOSMsg(QString key, QString val);
};

#endif // LIRCONTROLLER_H

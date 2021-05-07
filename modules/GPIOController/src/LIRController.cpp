#include "LIRController.h"
#include <iostream>


using namespace std;
LIRController::LIRController(QObject *parent) : QObject(parent)
{
  //   connect(&rangeTimer, &QTimer::timeout, this, &LIRController::getRanges);
}

bool LIRController::start()
{
    if( pigpio_daemon < 0 ){
    	int ret = pigpio_start(NULL,NULL);
    	if(ret < 0){
      		std::cout<<"ERROR in LIRController: COULD NOT CONNECT TO PIGPIOD DAEMON"<<std::endl;
        	return false;
    	}
    	pigpio_daemon = ret;
    }
    Init_Pigpiod(pigpio_daemon, sensor_list[LEFTSENSOR].bus, sensor_list[RIGHTSENSOR].bus, address);
    if(!sensor_list[LEFTSENSOR].setupComplete){
        sensor_list[LEFTSENSOR].setup();
    }
    if(!sensor_list[RIGHTSENSOR].setupComplete){
        sensor_list[RIGHTSENSOR].setup();
    }
    bool complete = sensor_list[LEFTSENSOR].setupComplete && sensor_list[RIGHTSENSOR].setupComplete;
    //    if(complete){
    // rangeTimer.start(500);
    //}
    return complete;
}


void LIRController::getRanges()
{
  double left_range = sensor_list[LEFTSENSOR].getRangeData();
  double right_range = sensor_list[RIGHTSENSOR].getRangeData();
  bool leftObj = (left_range < minRangeMM);
  bool rightObj = (right_range < minRangeMM);
  EnumDefs::SensorState state;
  //  std::string 
  if(leftObj && rightObj){
    state = EnumDefs::MIDDLE;
  } else if(leftObj) {
    state = EnumDefs::RIGHT;
  } else if(rightObj) {
    state = EnumDefs::LEFT;
  } else {
    state = EnumDefs::NONE;
  }
  //  std::cout<<"Left Range: "<<left_range<<". Right Range: "<<right_range<<std::endl;
  emit notifyMOOSMsg(QString::fromStdString(OBJECT_MSG), QString::number(int(state)));
}


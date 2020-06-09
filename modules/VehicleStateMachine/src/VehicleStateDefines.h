#ifndef VEHICLESTATEDEFINES_H
#define VEHICLESTATEDEFINES_H
#include <string>
#include <QString>
#include <stdlib.h>
#include <stdio.h>
#include <qmap.h>

enum VehicleStates{
    STANDBY,
    ALLSTOP,
    TELEOP,
    SWARMMODE
};

QMap<std::string, VehicleStates> vehicleStateMap = {
  {std::string("standby"),      STANDBY},
  {std::string("allstop"),      ALLSTOP},
  {std::string("teleop"),       TELEOP},
  {std::string("swarmmode"),    SWARMMODE},
};

VehicleStates getStateFromString(std::string state){
    return vehicleStateMap[QString::fromStdString(state).toLower().toStdString()];
}

std::string getStringFromState(VehicleStates state){
    return vehicleStateMap.key(state);
}

#endif // VEHICLESTATEDEFINES_H

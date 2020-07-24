#ifndef VEHICLESTATEDEFINES_H
#define VEHICLESTATEDEFINES_H

#include <QObject>
#include <QtCore>
#include <QString>
#include <cstdlib>
#include <ctime>

#define NUM_MAX_TIMEOUT 5

class EnumDefs : public QObject{
public:

    enum VehicleStates{
        STANDBY,
        ALLSTOP,
        TELEOP,
        SWARMMODE,
        DEMOMODE,
        UILAST,
        SWARMINIT,
        SWARMSTANDBY,
        SWARMRUN,
        ENUMLAST
    };
    Q_ENUM(VehicleStates)

   QMap<VehicleStates, QString> UIStateMap{{VehicleStates::STANDBY, "STANDBY"}, {VehicleStates::ALLSTOP, "ALLSTOP"},
                                         {VehicleStates::TELEOP, "TELEOP"},
                                         {VehicleStates::SWARMMODE, "SWARMMODE"},
                                         {VehicleStates::DEMOMODE, "DEMOMODE"},
                                         {VehicleStates::SWARMINIT, "SWARMINIT"},
                                         {VehicleStates::SWARMSTANDBY, "SWARMSTANDBY"},
                                         {VehicleStates::SWARMMODE, "SWARMMODE"},
                                         {VehicleStates::SWARMRUN, "SWARMRUN"}
                                         };

};






#endif // VEHICLESTATEDEFINES_H

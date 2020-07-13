#ifndef VEHICLESTATEDEFINES_H
#define VEHICLESTATEDEFINES_H

#include <QObject>
#include <QtCore>
#include <QString>


class EnumDefs : public QObject{
public:

    enum VehicleStates{
        STANDBY,
        ALLSTOP,
        TELEOP,
        SWARMMODE,
        DEMOMODE,
        ENUMLAST
    };
    Q_ENUM(VehicleStates)

   QMap<VehicleStates, QString> StateMap{{VehicleStates::STANDBY, "STANDBY"}, {VehicleStates::ALLSTOP, "ALLSTOP"},
                                         {VehicleStates::TELEOP, "TELEOP"},
                                         {VehicleStates::SWARMMODE, "SWARMMODE"},
                                         {VehicleStates::DEMOMODE, "DEMOMODE"}};




};

#endif // VEHICLESTATEDEFINES_H

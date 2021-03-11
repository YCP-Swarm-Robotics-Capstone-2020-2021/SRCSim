#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <QObject>
#include <QMap>
#include "Motor.h"

class MotorController : public QObject
{
    Q_OBJECT
public:
    explicit MotorController(QObject *parent = nullptr);

    QMap<SIDE, QList<Motor*>> motorMap;

signals:

};

#endif // MOTORCONTROLLER_H

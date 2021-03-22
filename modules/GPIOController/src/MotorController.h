#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <QObject>
#include <QMap>
#include <math.h>
#include "Motor.h"

const static double MS_TO_S = 1000.0;
class MotorController : public QObject
{
    Q_OBJECT
public:
    explicit MotorController(QObject *parent = nullptr);

    QMap<SIDE, QList<Motor*>> motorMap;
    void setOverride(bool on){override = on;}
    void onSpeedCurv(double speed, double curv, bool fromOverride = false);
    void onSpeedCurvOverride(double speed, double curv);
    void setupDeadbandRange(int h, int l);
    void start();

    double notifyCurrentSpeedInterval = 1.0;
    double maxSpeed = 1.5;

signals:
    void notifyMOOSMsg(QString key, QString val);
private:
    bool override = false;
};

#endif // MOTORCONTROLLER_H

#ifndef LIRCONTROLLER_H
#define LIRCONTROLLER_H

#include <QObject>
//#include "VL53L1X_api.h"
//#include "vl53l1_types.h"

class LIRController : public QObject
{
    Q_OBJECT
public:
    explicit LIRController(QObject *parent = nullptr);

signals:

};

#endif // LIRCONTROLLER_H

#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>

enum SIDE{
    LEFT,
    RIGHT
};

class Motor : public QObject
{
    Q_OBJECT
public:
    explicit Motor(QObject *parent = nullptr);

    int readGPIO;
    int writeGPIO;
    int maxRPM;
    int id;
    int cwhigh;
    int cwlow;
    int ccwhigh;
    int ccwlow;
    int dbhigh;
    int dblow;
    double rdhigh;
    double rdlow;
    bool reversed;
    int p;
    double i;
    double d;
    double wheelrad;
    SIDE side;



signals:

};

#endif // MOTOR_H

#include "Motor.h"

Motor::Motor(QObject *parent) : QObject(parent)
{
        readGPIO = 0;
        writeGPIO = 0;
        maxRPM = 0;
        id = 0;
        cwhigh = 0;
        cwlow = 0;
        ccwhigh = 0;
        ccwlow = 0;
        dbhigh = 0;
        dblow = 0;
        rdhigh = 0;
        rdlow = 0;
        reversed = 0;
        p = 0;
        i = 0;
        d = 0;
        wheelrad = 0;
        side = SIDE::LEFT;
}

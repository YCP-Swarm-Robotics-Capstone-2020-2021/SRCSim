#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H
#include <pigpiod_if2.h>
#include <VehicleStateDefines.h>
#include <QObject>
#include <QMap>

const static int set_led_freq = 500;
const static int HIGH = 1;
const static int LOW = 0;

enum LED_STATUS{
    OFF = 0,
    BLINKING,
    ON
};

class LED {
public:
    LED(){};
    ~LED(){}
    int id;
    int pin;
    LED_STATUS current_status = OFF;
    LED_STATUS status = OFF;
};

class LEDController : public QObject
{
    Q_OBJECT
public:
    LEDController();
    ~LEDController();

    void updateLEDStatus(EnumDefs::VehicleStates state);
    void updateConnectionLEDStatus(EnumDefs::ConnectionState state);
    QMap<int, LED> led_list;

    bool debug = false;
public slots:
    void setLEDs();
    void start();
private:
    QTimer set_timer;
    int pigpio_daemon;

};

#endif // LEDCONTROLLER_H

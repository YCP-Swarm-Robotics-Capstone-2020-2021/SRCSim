#include "LEDController.h"

LEDController::LEDController()
{
    connect(&set_timer, &QTimer::timeout, this, &LEDController::setLEDs);
    set_timer.start(set_led_freq);
}

LEDController::~LEDController(){

}

void LEDController::setLEDs()
{
    QMap<int, LED>::iterator iter = led_list.begin();
    while(iter != led_list.end()){
        int pin = iter.value().pin;
        int level = 0;
        int cur_val = gpio_read(pigpio_daemon, pin);
        LED_STATUS status = iter.value().status;
        switch(status){
            case LED_STATUS::ON:
                level = HIGH;
                break;
            case LED_STATUS::BLINKING:
                level = (cur_val == 0) ? HIGH : LOW;
                break;
            case LED_STATUS::OFF:
            default:
                level = LOW;
                break;
        }
        gpio_write(pigpio_daemon, pin, level);
    }
}


void LEDController::start()
{
    int ret = pigpio_start(NULL, NULL);
    if(ret < 0){return;}
    pigpio_daemon = ret;
    for(LED led : led_list.values()){
        set_mode(pigpio_daemon, led.pin, PI_OUTPUT);
    }
}

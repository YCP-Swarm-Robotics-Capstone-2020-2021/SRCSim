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

void LEDController::updateLEDStatus(EnumDefs::VehicleStates state, EnumDefs::ConnectionState connectionState)
{
    if(debug){
        for(auto led : led_list.values()){
            led.status = BLINKING;
        }
    }
    switch(state){
        case EnumDefs::STANDBY:
            led_list[2].status=OFF;
            led_list[3].status=OFF;
            led_list[4].status=OFF;
            led_list[0].status=OFF;
            break;
        case EnumDefs::TELEOP:
            led_list[2].status=OFF;
            led_list[3].status=OFF;
            led_list[4].status=ON;
            led_list[0].status=OFF;
            break;
        case EnumDefs::ALLSTOP:
            led_list[2].status=OFF;
            led_list[3].status=OFF;
            led_list[4].status=OFF;
            led_list[0].status=ON;
            break;
        case EnumDefs::DEMOMODE:
            led_list[2].status=OFF;
            led_list[3].status=ON;
            led_list[4].status=OFF;
            led_list[0].status=OFF;
            break;
        case EnumDefs::DODGE:
            led_list[2].status=ON;
            led_list[3].status=OFF;
            led_list[4].status=OFF;
            led_list[0].status=OFF;
            break;
        case EnumDefs::BOUNDARY:
            led_list[2].status=OFF;
            led_list[3].status=ON;
            led_list[4].status=ON;
            led_list[0].status=OFF;
            break;
        case EnumDefs::SWARMINIT:
            led_list[2].status=ON;
            led_list[3].status=OFF;
            led_list[4].status=ON;
            led_list[0].status=OFF;
            break;
        case EnumDefs::SWARMSTANDBY:
            led_list[2].status=ON;
            led_list[3].status=ON;
            led_list[4].status=OFF;
            led_list[0].status=OFF;
            break;
        case EnumDefs::SWARMRUN:
            led_list[2].status=ON;
            led_list[3].status=ON;
            led_list[4].status=ON;
            led_list[0].status=OFF;
            break;
        default:
            led_list[2].status=OFF;
            led_list[3].status=OFF;
            led_list[4].status=OFF;
            led_list[0].status=OFF;
            break;
    }
    switch(connectionState){
        case EnumDefs::CONNECTED:
            led_list[1].status = ON;
            break;
        case EnumDefs::DISCONNECTED:
            led_list[1].status = BLINKING;
            break;
        default:
            led_list[1].status = BLINKING;
            break;
    }
}

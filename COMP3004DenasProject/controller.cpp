#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{}

Controller::Controller(int battery)
{
    batteryLife = battery;
}


/*
 * Checks if battery is zero, if so then emit signal to close the device.
 * else return false
 */
bool Controller::checkIfBatteryIsZero()
{
    if(batteryLife <= 0){
        emit requestTurnOffDevice();
        return true;
    }
    return false;
}

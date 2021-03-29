#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{}

Controller::Controller(int battery)
{
    batteryLife = battery;
    treatmentList.push_back(new Allergy());
    treatmentList.push_back(new Head());
    treatmentList.push_back(new Hypotonia());
    treatmentList.push_back(new Throat());
    treatmentList.push_back(new SeventySevenHz());
    treatmentList.push_back(new SixtyHz());
    treatmentList.push_back(new TenHz());
    treatmentList.push_back(new TwentyHz());
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

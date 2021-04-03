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

    connectTreatmentSignals();
}


/*
 * Checks if battery is zero, if so then emit signal to close the device.
 * else return false
 */
bool Controller::checkIfBatteryIsZero()
{
    if(batteryLife <= 0){
        stopTimer();
        emit requestTurnOffDevice();
        return true;
    }
    return false;
}

void Controller::connectTreatmentSignals()
{
    for(unsigned long i = 0; i < treatmentList.size(); i++){
        connect(treatmentList[i],SIGNAL(sendBatteryUpdate(int)),this,SLOT(updateBattery(int)));
    }
}

void Controller::updateBattery(int p)
{
    checkIfBatteryIsZero();
    batteryLife -= p;
    emit changeGUIBattery(batteryLife);
}

void Controller::stopTimer()
{
    for(unsigned long i = 0; i < treatmentList.size(); i++){
        treatmentList[i]->stopTimer();
     }
}

/*
 * COMP3004 Project
 * DENAS PCM project by Steven Rhodes, Aaron Fisher, Joey Bitar, Colin Marsh, Ben Herron
 * Team 25
 */

#include "controller.h"
#include "recording.h"
#include <QDebug>
Controller::Controller(QObject *parent) : QObject(parent)
{}

using namespace std;

/*
 * Sets default values
 */
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
    treatmentActive = false;
}

Controller::~Controller(){
    for(unsigned long i = 0; i < treatmentList.size(); i++){
       delete treatmentList[i];
    }
    for(unsigned long i = 0; i < recordingList.size(); i++){
       delete recordingList[i];
    }
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

/*
 * COnnects all signals from the treatment Class
 */
void Controller::connectTreatmentSignals()
{
    for(unsigned long i = 0; i < treatmentList.size(); i++){
        connect(treatmentList[i],SIGNAL(sendBatteryUpdate(int)),this,SLOT(updateBattery(int)));
    }
}

/*
 * Update the battery consuming.
 */
void Controller::updateBattery(int p)
{
    /*
     * Since we do not want the device to be drained quickly we will only reduce the battery by power/2 if the power is greater than 10.
     */
    checkIfBatteryIsZero();
    if(p >= 10){
        batteryLife -= (p/2);
    }
    else{
        batteryLife -= p;
    }

    //Send the current battery to the GUI so it can update the slider.
    emit changeGUIBattery(batteryLife);
}

/*
 * Stop all timers for all treatments
 */
void Controller::stopTimer()
{
    for(unsigned long i = 0; i < treatmentList.size(); i++){
        treatmentList[i]->stopTimer();
     }
}

/*
 * REturns true is a treatment is in process else false
 */
bool Controller::isTreatmentActive()
{
    return treatmentActive;
}

/*
 * Start a treatment.
 * Sets the treatment flag to true
 */
void Controller::startTreatment()
{
    qDebug() <<"treatmentActive = true";
    treatmentActive = true;
}

/*
 * End a treatment
 * Sets the treatment flag to false
 */
void Controller::endTreatment()
{
    qDebug() <<"treatmentActive = false";
    treatmentActive = false;
}

/*
 * Adds a treatment to the list of recordings
 */
void Controller::addRecording(Treatment *t){
    Recording *r = new  Recording(t->takeDateScreenshot(),t->getProgram(),t->getMaxPower(),t->getDuration(),t->getFrequency());
    recordingList.push_back(r);
}

/*
 * Clears all recording history
 */
void Controller::clearRecordings(){
    for(unsigned long i = 0; i < recordingList.size(); i++){
        delete recordingList[i];
     }
    recordingList.clear();
}

/*
 * Restarts all timers from the treatment list.
 * Used for when the device is turned off and back on
 */
void Controller::reset(){
    for(unsigned long i = 0; i < treatmentList.size(); i++){
        treatmentList[i]->restartTimer();
     }
}

/*
 * Getter for the battery life.
 */
int Controller::getBattery(){
    return batteryLife;
}

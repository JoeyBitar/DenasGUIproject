/*
 * COMP3004 Project
 * DENAS PCM project by Steven Rhodes, Aaron Fisher, Joey Bitar, Colin Marsh, Ben Herron
 * Team 25
 */

#include "treatment.h"
#include <QDebug>
using namespace std;

Treatment::Treatment(QObject *parent) : QObject(parent)
{}

/*
 * Initialises instance variables
 */
Treatment::Treatment(QString programName, int powerLvl, int durationTime, int frequencyLvl)
{
    program    = programName;
    power      = powerLvl;
    maxPower   = power;
    duration   = durationTime;
    frequency  = frequencyLvl;

    /*
     * Sets the duration of the timer to be durationTime long.
     */
    timer.setHMS(0,durationTime,0);
    timerDuration.setHMS(0,0,0);
    timerCaller = new QTimer(this);
    connect(timerCaller, SIGNAL(timeout()), this, SLOT(decrementTimer()));
}

Treatment::~Treatment(){
    delete timerCaller;
}

/*
 * Getter for program treatment name
 */
QString Treatment::getProgram(){
    return program;
}

/*
 * GEtter for max power
 */
int Treatment::getMaxPower(){
    return maxPower;
}

/*
 * Starts the timer for the treatment
 */
void Treatment::startTimer()
{
    timerCaller->start(1000);
}

/*
 * Takes a screenshot and returns the date and time of whenever this function was called.
 */
QDateTime Treatment::takeDateScreenshot()
{
    /*
     * Date with exact time can be retrieved using date.toString("dd.MM.yyyy.hh:mm:ss")
    */
    dateTime = QDateTime::currentDateTime();
    return dateTime;
}

/*
 * Stops the treatment time. Usually if contact skin has been interrupted or if the treatment is over.
 */
void Treatment::stopTimer()
{
    timerCaller->stop();
}

/*
 * Returns the duration time of the treatment.
 * Will be used for the recording history.
 */
QString Treatment::getTreatmentDurationTime(){
    return timer.toString("mm:ss");
}

/*
 * Function is called every second and decreases the duration time every time by 1 second.
 */
void Treatment::decrementTimer()
{
    /*
     * need to send a signal to update the ui with timer.toString("mm:ss")
     */
    emit updateGUITimer(timer.toString("mm:ss"));
    emit sendBatteryUpdate(power);
    timer = timer.addSecs(-1);
    timerDuration = timerDuration.addSecs(+1);

    if(timer.toString("mm:ss") == "00:00"){
        stopTimer();
         QMessageBox b;
         b.setText("Treatment completed");
         b.exec();
    }
}

/*
 * Sets the power level
 */
void Treatment::setPower(int p)
{
    if(p>maxPower){
        maxPower= p;
    }
    power = p;
}

/*
 * Restarts both timers
 */
void Treatment::restartTimer()
{
    timer.setHMS(0,duration,0);
    timerDuration.setHMS(0,0,0);
}

/*
 * Getter for the duration(how long the treatment has been going on for)
 */
QString Treatment::getDuration()
{
    return timerDuration.toString("mm:ss");
}

/*
 * Getter for the treatment frequency
 */
int Treatment::getFrequency()
{
    return frequency;
}

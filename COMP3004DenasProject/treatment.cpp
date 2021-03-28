#include "treatment.h"

Treatment::Treatment(QObject *parent) : QObject(parent)
{}

/*
 * Initialises instance variables
 */

Treatment::Treatment(std::string programName, int powerLvl, int durationTime, int frequencyLvl)
{
    program   = programName;
    power     = powerLvl;
    duration  = durationTime;
    frequency = frequencyLvl;

    /*
     * Sets the duration of the timer to be durationTime long.
     */
    timer.setHMS(0,durationTime,0);
    timerCaller = new QTimer(this);

}

void Treatment::startTimer()
{
    connect(timerCaller, SIGNAL(timeout()), this, SLOT(decrementTimer()));
    timerCaller->start(1000);
}

void Treatment::stopTimer()
{
    timerCaller->stop();
}

void Treatment::decrementTimer()
{
    //need to send a signal to update the ui with timer.toString("mm:ss")

    timer = timer.addSecs(-1);

    if(timer.toString("mm:ss") == "00:00"){
        stopTimer();
    }
}

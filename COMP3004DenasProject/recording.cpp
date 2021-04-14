/*
 * COMP3004 Project
 * DENAS PCM project by Steven Rhodes, Aaron Fisher, Joey Bitar, Colin Marsh, Ben Herron
 * Team 25
 */

#include "recording.h"
#include <QDateTime>

Recording::Recording(QObject *parent) : QObject(parent)
{}

/*
 * Sets default values
 */
Recording::Recording(QDateTime date,QString p,int power,QString d){
    dateTime = date;
    program = p;
    maxPower = power;
    duration = d;
}

/*
 * Getter for date and time
 */
QString Recording::getDateTime(){
    QString *d = new QString(dateTime.toString());
    return *d;
}

/*
 * Getter for recording name
 */
QString Recording::getProgram(){
    QString *p = new QString(program);
    return *p;
}

/*
 * Returns recording power
 */
QString Recording::getMaxPower(){
    QString *mp = new QString();
    *mp= QString::number(maxPower);
    return *mp;
}
/*
 * Returns recording duration
 */
QString Recording::getDuration(){
    return duration;
}

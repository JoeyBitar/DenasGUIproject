#include "recording.h"
#include <QDateTime>

Recording::Recording(QObject *parent) : QObject(parent)
{}

Recording::Recording(QDateTime date,QString p,int power,QString d){
    dateTime = date;
    program = p;
    maxPower = power;
    duration = d;
}
QString Recording::getDateTime(){
    QString *d = new QString(dateTime.toString());
    return *d;
}

QString Recording::getProgram(){
    QString *p = new QString(program);
    return *p;
}

QString Recording::getMaxPower(){
    QString *mp = new QString();
    *mp= QString::number(maxPower);
    return *mp;
}
QString Recording::getDuration(){
    return duration;
}

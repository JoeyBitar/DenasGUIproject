#include "recording.h"
#include <QDateTime>
Recording::Recording(QObject *parent) : QObject(parent)
{}

Recording::Recording(QDateTime date,std::string p,int power,std::string d){
    dateTime = date;
    program = p;
    maxPower = power;
    duration = d;
}
Recording::~Recording()
{
}

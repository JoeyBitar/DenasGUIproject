#ifndef RECORDING_H
#define RECORDING_H

#include <QObject>
#include <QDateTime>
#include <iostream>
#include<sstream>

class Recording : public QObject
{
    Q_OBJECT
public:
    explicit Recording(QObject *parent = nullptr);
    Recording(QDateTime,QString,int,QString,int);       //constructor
    QString getDateTime();                          //Getter for date and time
    QString getProgram();                           //Getter for program name
    QString getMaxPower();                          //Getter for max power
    QString getDuration();                          //Getter for duration
    QString getFrequency();
private:
    QDateTime dateTime;                             //Date obj
    QString program;                                //Recording name
    int maxPower;                                   //Recording power
    QString duration;                               //Recording duration
    int frequency;                                  //Frequency

signals:

public slots:
};

#endif // RECORDING_H

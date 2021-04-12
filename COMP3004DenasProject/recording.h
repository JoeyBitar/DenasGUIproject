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
    Recording(QDateTime,QString,int,QString);
    QString getDateTime();
    QString getProgram();
    QString getMaxPower();
    QString getDuration();
private:
    QDateTime dateTime;
    QString program;
    int maxPower;
    QString duration;

signals:

public slots:
};

#endif // RECORDING_H

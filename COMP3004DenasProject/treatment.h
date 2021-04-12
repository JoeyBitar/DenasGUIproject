#ifndef TREATMENT_H
#define TREATMENT_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <string>
#include <QDateTime>
#include <iostream>

class Treatment : public QObject
{
    Q_OBJECT

public:
    explicit Treatment(QObject *parent = nullptr);
    Treatment(QString,int,int,int);
    void startTimer();                              //Starts the treatment timer
    void stopTimer();                               //Stops the treatment timer
    QString getTreatmentDurationTime();             //Returns the duration time left
    void setPower(int);
    QDateTime takeDateScreenshot();
    void restartTimer();
    QString getProgram();
    int getMaxPower();



private slots:
    void decrementTimer();                          //Decrements the treatment time every second.

signals:
    void updateGUITimer(QString);
    void sendBatteryUpdate(int);

private:
    QTimer* timerCaller;
    QTime timer;
    QDateTime dateTime;
    QString program;
    int power;
    int maxPower;
    int duration;
    int frequency;

};

#endif // TREATMENT_H

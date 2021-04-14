#ifndef TREATMENT_H
#define TREATMENT_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <string>
#include <QDateTime>
#include <iostream>
#include <QMessageBox>

class Treatment : public QObject
{
    Q_OBJECT

public:
    explicit Treatment(QObject *parent = nullptr);
    Treatment(QString,int,int,int);
    void startTimer();                              //Starts the treatment timer
    void stopTimer();                               //Stops the treatment timer
    QString getTreatmentDurationTime();             //Returns the duration time left
    void setPower(int);                             //Sets the power
    QDateTime takeDateScreenshot();                 //Takes a screenshot of the current date and time
    void restartTimer();                            //Restarts the timer object
    QString getProgram();                           //Gets the program name
    int getMaxPower();                              //Returns the max power
    QString getDuration();                          //Returnamount of time the user performed the treatment
    int getFrequency();                             //REturns the frequency of a treatment

private slots:
    void decrementTimer();                          //Decrements the treatment time every second.

signals:
    void updateGUITimer(QString);                   //Sends a signal
    void sendBatteryUpdate(int);                    //send a signal

private:
    QTimer* timerCaller;                            //timer for the treatment
    QTime timer;                                    //Holds the treatment time
    QTime timerDuration;                            //Holds the amount of time a user was in treatment for
    QDateTime dateTime;                             //Date
    QString program;                                //Treatment name
    int power;
    int maxPower;
    int duration;
    int frequency;

};

#endif // TREATMENT_H

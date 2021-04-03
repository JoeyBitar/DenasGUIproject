#ifndef TREATMENT_H
#define TREATMENT_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <string>
#include <QDateTime>

class Treatment : public QObject
{
    Q_OBJECT

public:
    explicit Treatment(QObject *parent = nullptr);
    Treatment(std::string,int,int,int);
    void startTimer();                              //Starts the treatment timer
    void pauseTimer();                              //Pauses the treatment timer
    void stopTimer();                               //Stops the treatment timer
    QString getTreatmentDurationTime();             //Returns the duration time left
    void setPower(int);

private slots:
    void decrementTimer();                          //Decrements the treatment time every second.

signals:
    void updateGUITimer(QString);
    void sendBatteryUpdate(int);

private:
    QTimer* timerCaller;
    QTime timer;
    QDateTime dateTime;
    std::string program;
    int power;
    int duration;
    int frequency;

};

#endif // TREATMENT_H

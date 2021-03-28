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
    void startTimer();
    void pauseTimer();
    void stopTimer();
    QString getTreatmentDurationTime();

private slots:
    void decrementTimer();

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

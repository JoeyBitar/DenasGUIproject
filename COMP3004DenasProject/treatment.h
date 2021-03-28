#ifndef TREATMENT_H
#define TREATMENT_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <string>


class Treatment : public QObject
{
    Q_OBJECT

public:
    explicit Treatment(QObject *parent = nullptr);
    Treatment(std::string,int,int,int);
    void startTimer();
    void pauseTimer();
    void stopTimer();

private slots:
    void decrementTimer();

private:
    QTimer* timerCaller;
    QTime timer;
    std::string program;
    int power;
    int duration;
    int frequency;

};

#endif // TREATMENT_H

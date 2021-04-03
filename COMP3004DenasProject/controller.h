#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <treatment.h>
#include <recording.h>
#include <vector>
#include <allergy.h>
#include <head.h>
#include <hypotonia.h>
#include <throat.h>
#include <seventysevenhz.h>
#include <sixtyhz.h>
#include <tenhz.h>
#include <twentyhz.h>



class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    Controller(int);
    std::vector<Treatment*> treatmentList;
    std::vector<Recording*> recordingList;
    void connectTreatmentSignals();
    void stopTimer();


signals:
    void requestTurnOffDevice();
    void changeGUIBattery(int);

private slots:
    void updateBattery(int);

private:
    void addRecordings(Treatment);
    void startTreatment();
    void pauseTreatment();
    void calculateBatteryDrainage();
    bool checkIfBatteryIsZero();

    int batteryLife;
    bool devicePower;

};

#endif // CONTROLLER_H

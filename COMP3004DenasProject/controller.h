#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <treatment.h>
#include <recording.h>
#include <vector>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    Controller(int);

signals:
    void requestTurnOffDevice();
    void changeGUIBattery(int);

private:
    void addRecordings(Treatment);
    void startTreatment();
    void pauseTreatment();
    void calculateBatteryDrainage();
    bool checkIfBatteryIsZero();
    void updateBattery(int);

    std::vector<Treatment> treatmentList;
    std::vector<Recording> recordingList;
    int batteryLife;
    bool devicePower;

};

#endif // CONTROLLER_H

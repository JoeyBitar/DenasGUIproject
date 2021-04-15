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
#include "treatment.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    Controller(int);
    ~Controller();
    std::vector<Treatment*> treatmentList;  //Hold all the treatment settings.
    std::vector<Recording*> recordingList;  //HOld a list of recording
    void connectTreatmentSignals();     //Connects all the signals
    void stopTimer();                   //Stop the timer
    void startTreatment();              //Start a treatment
    void endTreatment();                //End the treatment
    bool isTreatmentActive();           //INdicate true if treatment is in process
    void addRecording(Treatment*);      //Add a treatment to the recording history
    void clearRecordings();             //Clear recording list
    bool checkIfBatteryIsZero();        //CHeck if battery is 0
    void reset();                       //Reset timer
    int getBattery();                   //Getter for battery

signals:
    void requestTurnOffDevice();    //Emit to the gui to turn off device
    void changeGUIBattery(int);     //Emit battery for the GUI

private slots:
    void updateBattery(int);        //Receive signal from treatment

private:
    void addRecordings(Treatment);  //Add a treatment to the recording history
    void calculateBatteryDrainage();//Calculate battery drainage

    int batteryLife;                // Battery of the device
    bool devicePower;               // Bool to indicate if device is on or off
    bool treatmentActive;           // Bool to indicate if a treatment is in process.

};

#endif // CONTROLLER_H

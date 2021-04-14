#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <treatment.h>
#include <controller.h>
#include <qlcdnumber.h>
#include <string.h>
#include <QTableView>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr); //Constructor
    ~MainWindow();                                  //Destructor
    void connectTreatmentSignals();                 //Connects all signals
    void showPrograms();                            //Shows program menu
    void showFrequency();                           //Shows Frequency menu
    void showMainMenu();                            //Shows the main menu
    void showHistory();                             //Shows the history menu
    void showRecordings();                          //Shows all recordings
    void showPowerLevel();                          //Shows the power menu
    void showSaveOption();                          //Shows save option menu
    void disableOKButton();                         //Fixes the crash whenever the user presses ok during a treatment.
    void enableOKButton();                          //Fixes the crash whenever the user presses ok during a treatment.
    void disableSkin();                             //Fixes the crash whenever the user presses contact skin.
    void enableSkin();                              //Fixes the crash whenever the user presses contact skin.
    void showClearMessage();                        //Display pop-up message

private slots:
    void on_Up_clicked();                          //Slot for the up button
    void on_Down_clicked();                        //Slot for the down button
    void on_ok_clicked();                          //Slot for the ok button
    void turnOffDevice();                          //Slot for the turn off button
    void updateTimer(QString);                     //Slot for the update timer
    void on_returnMenu_clicked();                  //Slot for the return menu button
    void on_back_clicked();                        //Slot for the back menu button
    void updateBattery(int);                       //Slot for the update battery
    void on_contactSkin_clicked();                 //Slot for the contact skin button
    void on_turnOnOffDevice_clicked();

private:
    Ui::MainWindow *ui;
    Controller *control;                            //Control obj
    std::string prevMenu;                           //previous menu
    unsigned short currTreatment;                   //Indicates which treatment is being executed.
    QMessageBox clearMenu;                          //Pop-up message for clearing menu
    bool deviceOn;

};

#endif // MAINWINDOW_H

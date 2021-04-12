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


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectTreatmentSignals();
    void showPrograms();
    void showFrequency();
    void showMainMenu();
    void showHistory();
    void showRecordings();
    void showPowerLevel();
    void showSaveOption();
    void disableOKButton(); //Fixes the crash whenever the user presses ok during a treatment.
    void enableOKButton();
    void disableSkin();
    void enableSkin();

private slots:

    void on_Up_clicked();
    void on_Down_clicked();
    void on_ok_clicked();
    void turnOffDevice();
    void updateTimer(QString);
    void on_returnMenu_clicked();
    void on_back_clicked();
    void updateBattery(int);
    void on_contactSkin_clicked();

private:
    Ui::MainWindow *ui;
    Controller *control;
    std::string prevMenu;
    unsigned short currTreatment;
};

#endif // MAINWINDOW_H

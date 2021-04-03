#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <treatment.h>
#include <controller.h>
#include <qlcdnumber.h>
#include <string.h>

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
    void showHistory();
    void showPowerLevel();

private slots:

    void on_Up_clicked();
    void on_Down_clicked();
    void on_ok_clicked();
    void turnOffDevice();
    void updateTimer(QString);
    void on_returnMenu_clicked();
    void on_back_clicked();
    void updateBattery(int);

private:
    Ui::MainWindow *ui;
    Controller *control;
    std::string prevMenu;
};

#endif // MAINWINDOW_H

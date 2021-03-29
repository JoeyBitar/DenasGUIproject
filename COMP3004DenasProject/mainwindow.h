#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <treatment.h>
#include <controller.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Up_clicked();

    void on_Down_clicked();

    void on_powerIncrease_2_clicked();

    void turnOffDevice();

private:
    Ui::MainWindow *ui;
    Controller *control;
};

#endif // MAINWINDOW_H

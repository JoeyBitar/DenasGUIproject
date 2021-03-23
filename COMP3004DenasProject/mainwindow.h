#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

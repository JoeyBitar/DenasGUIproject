#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    control = new Controller(100); //Init controller
    connect(control, SIGNAL(requestTurnOffDevice()), this, SLOT(turnOffDevice())); //the turnOffDevice turns off the device or pop-ups a message or something.
    connectTreatmentSignals();


    //connect(ui->pushButton_7, SIGNAL(clicked()), ui->listWidget,
           // SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Connects all the treatments to the GUI, so the timer can be send to the GUI indicating how much time is left.
 */
void MainWindow::connectTreatmentSignals()
{
    for(unsigned long i = 0; i < control->treatmentList.size(); i++){
        connect(control->treatmentList[i],SIGNAL(updateGUITimer(QString)),this,SLOT(updateTimer(QString)));
    }
}

void MainWindow::on_Up_clicked()
{
    //int menuSize = ui->menu->count();
    int currentIndex = ui->menu->currentRow();
    if (currentIndex - 1 >= 0){
        ui->menu->setCurrentRow(currentIndex-1);
    }
}

void MainWindow::on_Down_clicked()
{
    int menuSize = ui->menu->count();
    int currentIndex = ui->menu->currentRow();
    qDebug() << "SIZE" << menuSize;
    if (currentIndex + 1 != menuSize){
        ui->menu->setCurrentRow(currentIndex+1);
    }
}

void MainWindow::on_ok_clicked()
{
    if(ui->menu->currentItem()->text() == "Programs"){
        ui->menu->clear();
        ui->menu->addItem("Allergy");
        ui->menu->addItem("Throad");
        ui->menu->addItem("Hypotonia");
        ui->menu->addItem("Head");
    }
}

/*
 * Connection already established with signals/slots
 */
void MainWindow::turnOffDevice()
{
    /*
     * do something to either turn off device or pop up a message.
     */
}

/*
 * Connection already established with signals/slots
 */
void MainWindow::updateTimer(QString time)
{

    /*
     * ui->something and update the time using the time local variable
     */
    qDebug() << time;
}

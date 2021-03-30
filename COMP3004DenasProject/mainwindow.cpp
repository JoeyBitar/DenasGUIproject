#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menu->setCurrentRow(0); // selects the "programs" menu by default

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

void MainWindow::showPrograms()
{
    ui->menu->clear();
    ui->menu->addItem("Allergy");
    ui->menu->addItem("Throad");
    ui->menu->addItem("Hypotonia");
    ui->menu->addItem("Head");
    ui->menu->setCurrentRow(0);
}

void MainWindow::showFrequency()
{
    ui->menu->clear();
    ui->menu->addItem("10Hz");
    ui->menu->addItem("20Hz");
    ui->menu->addItem("60Hz");
    ui->menu->addItem("77Hz");
    ui->menu->setCurrentRow(0);
}

void MainWindow::showHistory()
{
    ui->menu->clear();
    ui->menu->addItem("View");
    ui->menu->addItem("Clear");
    ui->menu->setCurrentRow(0);
}

void MainWindow::on_Up_clicked()
{
    //int menuSize = ui->menu->count();
    int currentIndex = ui->menu->currentRow();
    qDebug() << currentIndex;
    if (currentIndex - 1 >= 0){
        ui->menu->setCurrentRow(currentIndex-1);
    }
}

void MainWindow::on_Down_clicked()
{
    int menuSize = ui->menu->count();
    int currentIndex = ui->menu->currentRow();
    qDebug() << "SIZE" << menuSize;
    qDebug() << currentIndex;
    if (currentIndex + 1 != menuSize){
        ui->menu->setCurrentRow(currentIndex+1);
    }
}

void MainWindow::on_ok_clicked()
{
    if(ui->menu->currentItem()->text() == "Programs"){
        showPrograms();
    }
    else if(ui->menu->currentItem()->text() == "Frequency"){
        showFrequency();
    }
    else if(ui->menu->currentItem()->text() == "History"){
        showHistory();
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

void MainWindow::on_returnMenu_clicked()
{
    ui->menu->clear();
    ui->menu->addItem("Programs");
    ui->menu->addItem("Frequency");
    ui->menu->addItem("History");
    ui->menu->addItem("Med");
    ui->menu->addItem("Screening");
    ui->menu->setCurrentRow(0);
}

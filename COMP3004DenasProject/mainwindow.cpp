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
    connect(control, SIGNAL(changeGUIBattery(int)),this, SLOT(updateBattery(int))); //Connects the battery signal from Control class
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

enum string_code{
    eAllergy,
    eThroat,
    eHypotonia,
    eHead,
    e10Hz,
    e20Hz,
    e60Hz,
    e77Hz
};

string_code hash(std::string const& str){
    if (str == "Allergy") return eAllergy;
    if (str == "Throat") return eThroat;
    if (str == "Hypotonia") return eHypotonia;
    if (str == "Head") return eHead;
    if (str == "10Hz") return e10Hz;
    if (str == "20Hz") return e20Hz;
    if (str == "60Hz") return e60Hz;
    if (str == "77Hz") return e77Hz;
}

void MainWindow::showPrograms()
{
    ui->menu->clear();
    ui->menu->addItem("Allergy");
    ui->menu->addItem("Throat");
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

void MainWindow::showPowerLevel()
{
    ui->menu->clear();
    for(int i = 1; i < 101; i++){
        ui->menu->addItem(QString::number(i));
    }
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
    qDebug() << ui->menu->currentItem()->text();
    if(ui->menu->currentItem()->text() == "Programs"){
        showPrograms();
        prevMenu = "Main";
    }
    else if(ui->menu->currentItem()->text() == "Frequency"){
        showFrequency();
        prevMenu = "Main";
    }
    else if(ui->menu->currentItem()->text() == "History"){
        showHistory();
        prevMenu = "Main";
    }
    else if(ui->menu->currentItem()->text() == "View"){
        prevMenu = "History";
    }
    else if(ui->menu->currentItem()->text() == "Clear"){
        prevMenu = "History";
    }
    else if(ui->menu->currentItem()->text() == "Allergy"){
        showPowerLevel();
        prevMenu = "Allergy";
    }
    else if(ui->menu->currentItem()->text() == "Throat"){
        showPowerLevel();
        prevMenu = "Throat";
    }
    else if(ui->menu->currentItem()->text() == "Head"){
        showPowerLevel();
        prevMenu = "Head";
    }
    else if(ui->menu->currentItem()->text() == "Hypotonia"){
        showPowerLevel();
        prevMenu = "Hypotonia";
    }
    else if(ui->menu->currentItem()->text() == "10Hz"){
        showPowerLevel();
        prevMenu = "10Hz";
    }
    else if(ui->menu->currentItem()->text() == "20Hz"){
        showPowerLevel();
        prevMenu = "20Hz";
    }
    else if(ui->menu->currentItem()->text() == "60Hz"){
        showPowerLevel();
        prevMenu = "60Hz";
    }
    else if(ui->menu->currentItem()->text() == "77Hz"){
        showPowerLevel();
        prevMenu = "77Hz";
    }
    else if(ui->menu->currentItem()->text().toInt()){
        qDebug() << "Selected Power Level " << ui->menu->currentItem()->text();
        int powerlevel = ui->menu->currentItem()->text().toInt();
        control->treatmentList[0]->setPower(powerlevel);
        switch(hash(prevMenu)){
            case eAllergy:
                qDebug() << "Running Allergy at power level " << powerlevel;
                control->treatmentList[0]->startTimer();
                ui->menu->clear();
                break;

            case eThroat:
                 qDebug() << "Running Throat at power level " << powerlevel;
                 control->treatmentList[3]->startTimer();
                 ui->menu->clear();
                break;

            case eHead:
                 qDebug() << "Running Head at power level " << powerlevel;
                 control->treatmentList[1]->startTimer();
                 ui->menu->clear();
                break;

            case eHypotonia:
                 qDebug() << "Running Hypotonia at power level " << powerlevel;
                 control->treatmentList[2]->startTimer();
                 ui->menu->clear();
                break;

            case e10Hz:
                 qDebug() << "Running 10Hz at power level " << powerlevel;
                 control->treatmentList[6]->startTimer();
                 ui->menu->clear();

                break;

            case e20Hz:
                 qDebug() << "Running 20Hz at power level " << powerlevel;
                 control->treatmentList[7]->startTimer();
                 ui->menu->clear();
                break;

            case e60Hz:
                 qDebug() << "Running 60Hz at power level " << powerlevel;
                 control->treatmentList[5]->startTimer();
                 ui->menu->clear();
                break;

            case e77Hz:
                 qDebug() << "Running 77Hz at power level " << powerlevel;
                 control->treatmentList[4]->startTimer();
                 ui->menu->clear();
                break;
        }
    }
}

/*
 * Connection already established with signals/slots
 */
void MainWindow::turnOffDevice()
{
    ui->timer->setText(":(");
}

/*
 * Connection already established with signals/slots
 */
void MainWindow::updateTimer(QString time)
{

    /*
     * ui->something and update the time using the time local variable
     */


    QString limit = "00:00";
    ui->timer->setText(time);
    if (time == limit){
        qDebug() << "Timer Expired";
        ui->timer->clear();
        on_back_clicked();
    }
    qDebug() << time;
}

void MainWindow::on_returnMenu_clicked()
{
    ui->menu->clear();
    ui->timer->clear();
    ui->menu->addItem("Programs");
    ui->menu->addItem("Frequency");
    ui->menu->addItem("History");
    ui->menu->addItem("Med");
    ui->menu->addItem("Screening");
    ui->menu->setCurrentRow(0);
}

void MainWindow::on_back_clicked()
{
    ui->timer->clear();
    if(prevMenu == "Programs"){
        showPrograms();
    }
    else if(prevMenu == "Frequency"){
        showFrequency();
    }
    else if(prevMenu == "History"){
        showHistory();
    }
    else if(prevMenu == "Main"){
        on_returnMenu_clicked();
    }
    else if(prevMenu == "Allergy" || prevMenu == "Throat" || prevMenu == "Head" || prevMenu == "Hypotonia"){
        showPrograms();
    }
    else if(prevMenu == "10Hz" || prevMenu == "20Hz" || prevMenu == "60Hz" || prevMenu == "77Hz"){
        showFrequency();
    }
    prevMenu = "Main";
}

void MainWindow::updateBattery(int b)
{
    ui->progressBar->setValue(b);
}

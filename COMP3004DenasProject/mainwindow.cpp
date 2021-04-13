/*
 * COMP3004 Project
 * DENAS PCM project by Steven Rhodes, Aaron Fisher, Joey Bitar, Colin Marsh, Ben Herron
 * Team 25
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menu->setCurrentRow(0);                                                     // selects the "programs" menu by default
    ui->tableWidget->hide();                                                        // Hides the recording table widget
    prevMenu = "Main";                                                              //Sets the default value for the prevMenu

    control = new Controller(100);                                                  //Init controller
    connect(control, SIGNAL(requestTurnOffDevice()), this, SLOT(turnOffDevice()));  //the turnOffDevice turns off the device or pop-ups a message or something.
    connect(control, SIGNAL(changeGUIBattery(int)),this, SLOT(updateBattery(int))); //Connects the battery signal from Control class
    connectTreatmentSignals();                                                      //Connects treatment signals
    disableSkin();                                                                  //Disables contact skin until treatment starts
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

/*
 * Enum for the treatments
 */
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

/*
 *Returns string_code from eNum
 */
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

/*
 * Shows the main menu
 */
void MainWindow::showMainMenu(){
    ui->timer->clear();
    ui->menu->clear();
    ui->menu->addItem("Programs");
    ui->menu->addItem("Frequency");
    ui->menu->addItem("History");
    ui->menu->addItem("Med");
    ui->menu->addItem("Screening");
    ui->menu->setCurrentRow(0);
}

/*
 * Shows the programs menu
 */
void MainWindow::showPrograms()
{
    ui->menu->clear();
    ui->menu->addItem("Allergy");
    ui->menu->addItem("Throat");
    ui->menu->addItem("Hypotonia");
    ui->menu->addItem("Head");
    ui->menu->setCurrentRow(0);
}

/*
 * Shows the frequency menu
 */
void MainWindow::showFrequency()
{
    ui->menu->clear();
    ui->menu->addItem("10Hz");
    ui->menu->addItem("20Hz");
    ui->menu->addItem("60Hz");
    ui->menu->addItem("77Hz");
    ui->menu->setCurrentRow(0);
}

/*
 * Shows the history menu
 */
void MainWindow::showHistory()
{
    ui->menu->clear();
    ui->menu->addItem("View");
    ui->menu->addItem("Clear");
    ui->menu->setCurrentRow(0);
}

/*
 * Shows the "after treatment" menu
 */
void MainWindow::showSaveOption()
{
    ui->menu->clear();
    ui->menu->addItem("Save Recording");
    ui->menu->addItem("Discard Recording");
    ui->menu->addItem("Return to Treatment");
    ui->menu->setCurrentRow(0);
}

/*
 * Shows the power selection menu
 */
void MainWindow::showPowerLevel()
{
    ui->menu->clear();
    for(int i = 1; i < 101; i++){
        ui->menu->addItem(QString::number(i));
    }
    ui->menu->setCurrentRow(0);
}

/*
 * Slot to move ui selection menu to the top
 */
void MainWindow::on_Up_clicked()
{
    int currentIndex = ui->menu->currentRow();
    if (currentIndex - 1 >= 0){
        ui->menu->setCurrentRow(currentIndex-1);
    }
}


/*
 * Slot to move ui selection menu to the bottom
 */
void MainWindow::on_Down_clicked()
{
    int menuSize = ui->menu->count();
    int currentIndex = ui->menu->currentRow();
    if (currentIndex + 1 != menuSize){
        ui->menu->setCurrentRow(currentIndex+1);
    }
}

/*
 * Shows all the saved recordings using QTableWidgetItem
 */
void MainWindow::showRecordings(){
    ui->menu->hide(); //Hides the menu in order to show the QTableWidget

    QTableWidgetItem *item = new QTableWidgetItem("Date",0);
    QTableWidgetItem *item1 = new QTableWidgetItem("Treatment",0);
    QTableWidgetItem *item2 = new QTableWidgetItem("Power",0);
    QTableWidgetItem *item3 = new QTableWidgetItem("Duration",0);
    ui->tableWidget->setRowCount(control->recordingList.size() + 1);
    ui->tableWidget->setColumnCount(4);

    ui->tableWidget->setItem(0,0,item);
    ui->tableWidget->setItem(0,1,item1);
    ui->tableWidget->setItem(0,2,item2);
    ui->tableWidget->setItem(0,3,item3);
    ui->tableWidget->show();
    for(int i=0;i< control->recordingList.size();i++){
        QTableWidgetItem *dateTime = new QTableWidgetItem(control->recordingList[i]->getDateTime(),0);
        ui->tableWidget->setItem(i+1,0,dateTime);

        QTableWidgetItem *program = new QTableWidgetItem(control->recordingList[i]->getProgram(),0);
        ui->tableWidget->setItem(i+1,1,program);

        QTableWidgetItem *maxPower = new QTableWidgetItem(control->recordingList[i]->getMaxPower(),0);
        ui->tableWidget->setItem(i+1,2,maxPower);

        QTableWidgetItem *duration = new QTableWidgetItem(control->recordingList[i]->getDuration(),0);
        ui->tableWidget->setItem(i+1,3,duration);
    }
}

/*
 * Slots which handles the "ok" button click
 */
void MainWindow::on_ok_clicked()
{
    /*
     * If user selects the "Programs" menu. Display the program menu.
     */
    if(ui->menu->currentItem()->text() == "Programs"){
        showPrograms();
        prevMenu = "Main";
    }
    /*
     * If user selects the "Frequency" menu. Display the Frequency menu.
     */
    else if(ui->menu->currentItem()->text() == "Frequency"){
        showFrequency();
        prevMenu = "Main";
    }
    /*
     * If user selects the "History" menu. Display the History menu.
     */
    else if(ui->menu->currentItem()->text() == "History"){
        showHistory();
        prevMenu = "Main";
    }
    /*
     * If user selects the "View" menu. Display all recordings.
     */
    else if(ui->menu->currentItem()->text() == "View"){
        prevMenu = "History";
        showRecordings();
    }
    /*
     * If user selects the "Clear" menu. Clear all recordings.
     */
    else if(ui->menu->currentItem()->text() == "Clear"){
        prevMenu = "History";
        showClearMessage();
    }
    /*
     * If user selects the "Allergy" menu. Show the power levels
     */
    else if(ui->menu->currentItem()->text() == "Allergy"){
        showPowerLevel();
        prevMenu = "Allergy";
        currTreatment = 0;
    }
    /*
     * If user selects the "Throat" menu. Show the power levels
     */
    else if(ui->menu->currentItem()->text() == "Throat"){
        showPowerLevel();
        prevMenu = "Throat";
        currTreatment = 3;
    }
    /*
     * If user selects the "Head" menu. Show the power levels
     */
    else if(ui->menu->currentItem()->text() == "Head"){
        showPowerLevel();
        prevMenu = "Head";
        currTreatment = 1;
    }
    /*
     * If user selects the "Hypotonia" menu. Show the power levels
     */
    else if(ui->menu->currentItem()->text() == "Hypotonia"){
        showPowerLevel();
        prevMenu = "Hypotonia";
        currTreatment = 2;
    }
    /*
     * If user selects the "10Hz" menu. Show the power levels
     */
    else if(ui->menu->currentItem()->text() == "10Hz"){
        showPowerLevel();
        prevMenu = "10Hz";
        currTreatment = 6;
    }
    /*
     * If user selects the "20Hz" menu. Show the power levels
     */
    else if(ui->menu->currentItem()->text() == "20Hz"){
        showPowerLevel();
        prevMenu = "20Hz";
        currTreatment = 7;
    }
    /*
     * If user selects the "60Hz" menu. Show the power levels
     */
    else if(ui->menu->currentItem()->text() == "60Hz"){
        showPowerLevel();
        prevMenu = "60Hz";
        currTreatment = 5;
    }
    /*
     * If user selects the "77Hz" menu. Show the power levels
     */
    else if(ui->menu->currentItem()->text() == "77Hz"){
        showPowerLevel();
        prevMenu = "77Hz";
        currTreatment = 4;
    }
    /*
     * If user selects the "Save Recording" menu. Save the recording.
     */
    else if(ui->menu->currentItem()->text() == "Save Recording"){
        qDebug() << "Recording Saved";
        control->treatmentList[currTreatment]->restartTimer();
        control->endTreatment();
        control->treatmentList[currTreatment]->getProgram();
        control->addRecording(control->treatmentList[currTreatment]);
        showMainMenu();
        disableSkin();
        prevMenu = "Main";
    }
    /*
     * If user selects the "Discard Recording" menu. Discard the treatment and redirect user to main menu.
     */
    else if(ui->menu->currentItem()->text() == "Discard Recording"){
        qDebug() << "Recording discarded ";
        control->treatmentList[currTreatment]->restartTimer();
        control->endTreatment();
        disableSkin();
        showMainMenu();
        prevMenu = "Main";
    }
    /*
     * If user selects the "Return to Treatment" menu. Redirect user to the treatment.
     */
    else if(ui->menu->currentItem()->text() == "Return to Treatment"){
        qDebug() << "Returning to treatment";
        disableOKButton();
        ui->menu->clear();
        ui->timer->setText("Skin");
        prevMenu = "Power";
        /*
         * Fixes crashing bug. Doesn't allow user to press contact skin if the timer is done.
         */
        if(control->treatmentList[currTreatment]->getTreatmentDurationTime() == "00:00"){
            disableSkin();
        }
        else{
          enableSkin();
        }
    }
    /*
     * Loads up treatment when power level is selected.
     */
    else if(ui->menu->currentItem()->text().toInt()){
        qDebug() << "Selected Power Level " << ui->menu->currentItem()->text();
        disableOKButton();                                                                    //Disables ok button. Fixes crash
        enableSkin();                                                                         //Disables ok button. Fixes crash
        int powerlevel = ui->menu->currentItem()->text().toInt();
        control->startTreatment();                                                            //Starts the treatment
        control->treatmentList[0]->setPower(powerlevel);                                      //Sets the power level
        ui->powerSlider->setValue(powerlevel);                                                //Sets the power slider. Just for visual purposes.
        ui->frequencySlider->setValue(control->treatmentList[currTreatment]->getFrequency()); //Sets the frequency slider. Just for visual purposes.
        /*
         * For each treatment, sets its power level, and sets the timer widget.
         */
        switch(hash(prevMenu)){
            case eAllergy:
                qDebug() << "Running Allergy at power level " << powerlevel;
                control->treatmentList[0]->setPower(powerlevel);
                ui->timer->setText("Skin");
                ui->menu->clear();
                break;

            case eThroat:
                 qDebug() << "Running Throat at power level " << powerlevel;
                 control->treatmentList[3]->setPower(powerlevel);
                 ui->timer->setText("Skin");
                 ui->menu->clear();
                break;

            case eHead:
                 qDebug() << "Running Head at power level " << powerlevel;
                 control->treatmentList[1]->setPower(powerlevel);
                 ui->timer->setText("Skin");
                 ui->menu->clear();
                break;

            case eHypotonia:
                 qDebug() << "Running Hypotonia at power level " << powerlevel;
                 control->treatmentList[2]->setPower(powerlevel);
                 ui->timer->setText("Skin");
                 ui->menu->clear();
                break;

            case e10Hz:
                 qDebug() << "Running 10Hz at power level " << powerlevel;
                 control->treatmentList[6]->setPower(powerlevel);
                 ui->timer->setText("Skin");
                 ui->menu->clear();

                break;

            case e20Hz:
                 qDebug() << "Running 20Hz at power level " << powerlevel;ui->contactSkin->setChecked(false);
                 control->treatmentList[7]->setPower(powerlevel);
                 ui->timer->setText("Skin");
                 ui->menu->clear();
                break;

            case e60Hz:
                 qDebug() << "Running 60Hz at power level " << powerlevel;
                 control->treatmentList[5]->setPower(powerlevel);
                 ui->timer->setText("Skin");
                 ui->menu->clear();
                break;

            case e77Hz:
                 qDebug() << "Running 77Hz at power level " << powerlevel;
                 control->treatmentList[4]->setPower(powerlevel);
                 ui->timer->setText("Skin");
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
    control->stopTimer();
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
    QString limit = "00:01";
    ui->timer->setText(time);
    if (time == limit){
        qDebug() << "Timer Expired";
        ui->timer->setText("DONE");
        disableSkin();
    }
    qDebug() << time;
}

/*
 * Returns to the main menu
 */
void MainWindow::on_returnMenu_clicked()
{
    enableOKButton();                       //Renables ok button
    ui->contactSkin->setChecked(false);     //Disables contact skin button
    ui->timer->clear();                     //Clears timer
    ui->menu->clear();                      //Clears the old menu
    control->stopTimer();                   //Stops all timers
    /*
     * If treatment was active then prompt the user to save or discard treatment.
     */
    if(control->isTreatmentActive()==true){
       showSaveOption();
       ui->menu->setCurrentRow(0);
    }else{
        ui->tableWidget->hide();
        ui->menu->setVisible(true);
        showMainMenu();
    }
}

/*
 * Slot for the back button.
 * Brings the user to the previous menu based on the prevMenu variable.
 */
void MainWindow::on_back_clicked()
{
    enableOKButton();                   //Enables the ok button
    disableSkin();                      //Disables skin button
    ui->contactSkin->setChecked(false); //Disables skin button selection
    ui->timer->clear();                 //Clears the timer
    ui->menu->clear();                  //Clears the old timer
    control->stopTimer();               //Stops timer
    /*
     * If treatment was active then prompt the user to save or discard treatment.
     */
    if(control->isTreatmentActive()==true){
       showSaveOption();
       ui->menu->setCurrentRow(0);
    }
    /*
     * Return to programs
     */
    else if(prevMenu == "Programs"){
        showPrograms();
    }
    /*
     * Return to Frequency
     */
    else if(prevMenu == "Frequency"){
        showFrequency();
    }
    /*
     * Return to History
     */
    else if(prevMenu == "History"){
        ui->tableWidget->hide();
        ui->menu->setVisible(true);
        showHistory();
    }
    /*
     * Return to Main
     */
    else if(prevMenu == "Main"){
        on_returnMenu_clicked();
    }
    /*
     * Return to Programs
     */
    else if(prevMenu == "Allergy" || prevMenu == "Throat" || prevMenu == "Head" || prevMenu == "Hypotonia"){
        showPrograms();
    }
    /*
     * Return to Frequency
     */
    else if(prevMenu == "10Hz" || prevMenu == "20Hz" || prevMenu == "60Hz" || prevMenu == "77Hz"){
        showFrequency();
    }
    prevMenu = "Main";
}

/*
 *  Updates timer every time the QTimer sends a signal with the new time
 */
void MainWindow::updateBattery(int b)
{
    ui->progressBar->setValue(b);
}

/*
 * Simulates the contact skin feature
 */
void MainWindow::on_contactSkin_clicked()
{
    if(ui->contactSkin->isChecked()){
         control->treatmentList[currTreatment]->startTimer();
    }
    else{
        control->treatmentList[currTreatment]->stopTimer();
    }
}
/*
 * Disables the OK button
 */
void MainWindow::disableOKButton()
{
    ui->ok->setEnabled(false);
}
/*
 * Enables the OK button
 */
void MainWindow::enableOKButton()
{
    ui->ok->setEnabled(true);
}
/*
 * Disables the skin radio button
 */
void MainWindow::disableSkin()
{
      ui->contactSkin->setEnabled(false);
}
/*
 * Enables the skin radio button
 */
void MainWindow::enableSkin()
{
      ui->contactSkin->setEnabled(true);
}

/*
 * Pop-up message indicating a treatment was saved.
 */
void MainWindow::showClearMessage()
{
    control->clearRecordings();
    clearMenu.setText("Treatment recordings has been cleared");
    clearMenu.exec();
}

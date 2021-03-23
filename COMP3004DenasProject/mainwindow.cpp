#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //connect(ui->pushButton_7, SIGNAL(clicked()), ui->listWidget,
           // SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
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


void MainWindow::on_powerIncrease_2_clicked()
{
    qDebug() << "Menu option: " <<ui->menu->currentItem()->text() << " has been clicked";
    if(ui->menu->currentItem()->text() == "Programs"){
        qDebug() << "True";

    }
}

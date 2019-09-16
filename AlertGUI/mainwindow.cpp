#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    decoder = new DataDecoder(&container);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkAlerts(){
    if(decoder->sendExitAlert()== true){
       QMessageBox::warning(this, tr("ERROR MESSAGE"), tr("A Swarm of Bees is Leaving the Hive!"));
       //ui->setupUi(this);
    }
    if(decoder->sendEntryAlert()==true){
        QMessageBox::warning(this, tr("ERROR MESSAGE"), tr("A Swarm of Bees is Entering the Hive!"));
    }


}



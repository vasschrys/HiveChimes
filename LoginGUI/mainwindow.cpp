#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <QMessageBox>


using namespace  std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    char** P_rows =hives->select_table_h();
    QString added;
    hives->add_row_h(0,"HD002","shiho","HD002ModelDB");
    hives->add_row_h(1,"HD003","Jon","HD003ModelDB");
    hives->add_row_h(2,"HD004","Basit","HD004ModelDB");

    if(P_rows!=nullptr){
        for(int i =4; i<4*(hives->size()+1);i=i+4){
            added=P_rows[i+1];
            ui->comboBox->addItem(added);
            //std::cout <<P_rows[i+1]<< P_rows[i+2]<<P_rows[i+3] << std::endl;
        }
    }

    //call new diaglougue
    introWindow = new Intro();
    introWindow->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * @brief MainWindow::on_pushButton_2_clicked - This method determines the next Window to be popped up, with the conditions
 * based on the GUI. The method also determines the Guis to be displayed after the first one. All GUIs to display
 * are determined in this method.
 */
void MainWindow::on_pushButton_2_clicked()
{
    if(w!=nullptr){
        w->close();
        w->~MainWindowAnimate();
        w=nullptr;
    }
    if(graphModel!=nullptr){
        graphModel->close();
        graphModel->~Bees();
        graphModel=nullptr;
    }
    string nessicarty;
    if((!ui->checkBox->isChecked() && !ui->checkBox_2->isChecked()) ||
            (ui->checkBox->isChecked() && ui->checkBox_2->isChecked())){
        QMessageBox::warning(this, tr("ERROR MESSAGE"), tr("Check one box before continuing"));
    }
    //general user
    else {
        if( ui->checkBox->isChecked()){

            secWindowGen = new secondWindow(this);
            secWindowGen->exec();


            //std::cout << secWindowGen->realTime <<endl;
            if(secWindowGen->realTime ==true){
                w = new MainWindowAnimate(this);
                //cout << "SEC SOUND "<< secWindowGen->getPlaySound();
                w->setSound(secWindowGen->getPlaySound());
                w->createEnvironment();
                w->show();
            }else if(secWindowGen->viewModel ==true){
                nessicarty=hiveid.toStdString()+"ModelDB";
                usm = new userSelectModel(this,dbtable,&nessicarty);
                usm->exec();
                if(usm->loop){
                graphModel = new Bees(this, usm->data);
                graphModel->show();
                }
            }

        }

        //researcher
        else if(ui->checkBox_2->isChecked()){
            reseacherWindow = new secondWindowResearcher(this, &hiveid);
            reseacherWindow->exec();

            if(reseacherWindow->rawData == true){
                realTimeWindow = new MainWindowRT(this);
                realTimeWindow->show();
            }

            else if(reseacherWindow->realTime == true){
                w = new MainWindowAnimate(this);
                //cout << "SEC SOUND "<< secWindowGen->getPlaySound();
                w->setSound(reseacherWindow->getPlaySound());
                w->createEnvironment();
                w->show();
            }
            else if(reseacherWindow->createModel == true){
                createModel = new CreateModel(this, &hiveid, dbtable);
                createModel->exec();
                if(createModel->generate==true){
                    generateModel = new GeneratedModel(this, &hiveid, &createModel->modeltitle,&createModel->size, &createModel->date,
                                                       &createModel->times, &createModel->duration,dbtable);
                    generateModel->show();
                    graphModel = new Bees(this, generateModel->beelog);
                    graphModel->show();
                }
            }
            else if(reseacherWindow->viewModel ==true){
                nessicarty=hiveid.toStdString()+"ModelDB";
                usm = new userSelectModel(this,dbtable,&nessicarty);
                usm->exec();
                if(usm->loop){
                graphModel = new Bees(this, usm->data);
                graphModel->show();
                }
            }

        }

    }

}


/**
 * @brief MainWindow::on_comboBox_currentIndexChanged - This method takes in an argument which determines the HiveID, and sets it to the
 * variable that represents the HiveID.
 * @param arg1
 */
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    hiveid=arg1;
    //std::cout<<&hiveid<<endl;
}

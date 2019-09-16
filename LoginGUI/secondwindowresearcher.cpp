/**This class is for a user who has selected the box indicating that they are a Researcher.
  **/

#include "secondwindowresearcher.h"
#include "ui_secondwindowresearcher.h"
#include <QMessageBox>

secondWindowResearcher::secondWindowResearcher(QWidget *parent,QString *hivename) :
    QDialog(parent),
    ui(new Ui::secondWindowResearcher)
{
    ui->setupUi(this);
    ui->label->setText(*hivename);
}

secondWindowResearcher::~secondWindowResearcher()
{
    delete ui;
}

/**
 * @brief secondWindowResearcher::on_pushButton_clicked - This method determines which box is checked by the researcher after they have selected
 * that they are a general user. This determines which functionalities the researcher would like to use as they are logged in the program,
 * using checkboxes displayed on the GUI
 */
void secondWindowResearcher::on_pushButton_clicked()
{
    QString Hiveid=ui->label->text();

    if(((!ui->checkBox_2->isChecked() && !ui->checkBox_3->isChecked()) && !ui->checkBox_4->isChecked() && !ui->checkBox_5->isChecked()) ||
           (ui->checkBox_2->isChecked() && ui->checkBox_3->isChecked() && ui->checkBox_4->isChecked() && ui->checkBox_5->isChecked()) ||
            (ui->checkBox_2->isChecked() && ui->checkBox_3->isChecked() && ui->checkBox_4->isChecked()) ||
             (ui->checkBox_2->isChecked() && ui->checkBox_3->isChecked()) ||
            (ui->checkBox_2->isChecked() &&  ui->checkBox_4->isChecked()) || (ui->checkBox_3->isChecked() && ui->checkBox_4->isChecked()) ||
            ui->checkBox_4->isChecked() && ui->checkBox_5->isChecked() || ui->checkBox_3->isChecked() && ui->checkBox_4->isChecked() && ui->checkBox_5->isChecked()){
        QMessageBox::warning(this, tr("ERROR MESSAGE"), tr("Check one box before continuing"));
    }

    else{
        if(ui->checkBox_2->isChecked()){
            // animateW->show();
            //playSound = true;
            realTime = true;
            this->hide();
            //this->destroy();
        }
        else if(ui->checkBox_5->isChecked()){
            rawData = true;
            this->hide();
        }else if(ui->checkBox_4->isChecked()){
            createModel = true;
            this->hide();
        }else if(ui->checkBox_3->isChecked()){
            viewModel = true;
            this->hide();
        }
    }


}

/**
 * @brief secondWindowResearcher::getPlaySound - This method returns whether the sound should be played on the visualization GUI
 * @return - the sound
 */
bool secondWindowResearcher::getPlaySound(){
    return playSound;
}

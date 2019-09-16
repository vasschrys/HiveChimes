/**This class is for General Uses, it is the Gui that controls which Gui's will be displayed for a General User.
  **/

#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QMessageBox>


secondWindow::secondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondWindow)
{
    mainWindow = parent;

    ui->setupUi(this);
}

secondWindow::~secondWindow()
{
    mainWindow->show();
    delete ui;
}

/**
 * @brief secondWindow::on_pushButton_clicked - This method determines which box is checked by the User after they have selected
 * that they are a general user.
 */
void secondWindow::on_pushButton_clicked()
{

    if((ui->checkBox->isChecked() && ui->checkBox_3->isChecked())||
           (!ui->checkBox->isChecked() && !ui->checkBox_3->isChecked())){
        QMessageBox::warning(this, tr("ERROR MESSAGE"), tr("Check one box before continuing"));
    }
    else{
        if(ui->checkBox_3->isChecked()){
            // userSelect = new userSelectModel(this);
            //userSelect->show();
            viewModel = true;
            this->hide();
        }else if(ui->checkBox->isChecked()){
            // animateW->show();
            playSound = true;
            realTime = true;
            this->hide();


        }
    }

}

/**
 * @brief secondWindow::getPlaySound - This method returns whether the sound should be played on the visualization GUI
 * @return
 */
bool secondWindow::getPlaySound(){
    return playSound;
}



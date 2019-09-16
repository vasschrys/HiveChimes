/**This Class contains the initial GUI displaying the information on how to run the program
 * as well as each of our group member's name.
**/

#include "intro.h"
#include "ui_intro.h"

Intro::Intro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Intro)
{
    ui->setupUi(this);
}

Intro::~Intro()
{
    delete ui;
}

/**
 * @brief Intro::on_pushButton_clicked - This method when triggered by the button being clicked closes the window
 */
void Intro::on_pushButton_clicked()
{
    delete this;
}

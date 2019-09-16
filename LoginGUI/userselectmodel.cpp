#include "userselectmodel.h"
#include "ui_userselectmodel.h"

userSelectModel::userSelectModel(QWidget *parent,Tool *tool,string *tablename) :
    QDialog(parent),
    ui(new Ui::userSelectModel)
{
    ui->setupUi(this);
    dbtool=tool;
    //cout<<*tablename<<endl;
    models=new DBModelTable(tool,*tablename);
    char** P_rows =models->select_table_m();
    QString added;
    if(P_rows!=nullptr){
        for(int i =3; i<3*(models->size()+1);i=i+3){
            added=P_rows[i+2];
            ui->ModelList->addItem(added);
            //std::cout <<P_rows[i]<< P_rows[i+1]<<P_rows[i+2] << std::endl;
        }
    }
}

userSelectModel::~userSelectModel()
{
    delete ui;
}

/**
 * @brief userSelectModel::on_pushButton_clicked - This method is triggered when the continue button is pressed, takes what model
 * name the user selected and retreives it from the datacontainer.
 */
void userSelectModel::on_pushButton_clicked()
{
    data=new DataContainer(dbtool,modelname);
    this->hide();
}

/**
 * @brief userSelectModel::on_ModelList_itemClicked - This method takes in the selected model name form the screen in order to get the
 * the correct model
 * @param item
 */
void userSelectModel::on_ModelList_itemClicked(QListWidgetItem *item)
{
    loop=true;
    modelname=item->text().toStdString();
}

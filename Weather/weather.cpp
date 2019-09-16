#include "weather.h"
#include "ui_weather.h"

Weather::Weather(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Weather)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    temp_board="";
    createBoard();
    loadLabel();
}



Weather::~Weather()
{
    delete ui;
}


void Weather::get_Temp(){
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://qt.nokia.com")));
}

/**
 *Create a single string from the array that stores the gameboard
 * */
void Weather::createBoard(){
    for(int row = 0; row < bee_test.get_num_rows(); row++) {
        for(int col = 0; col < bee_test.get_num_cols(); col++) {
            temp_board += bee_test.getBrdSpc(row,col);
        }
        temp_board += '\n';
    }
}

/**
 * Loads the QString into the label
 * */
void Weather::loadLabel(){
    ui->label_2->setText(temp_board);
}


/**
 * Clears the board
 * */
void Weather::clearBoard(){
    ui->label_2->clear();
}

void Weather::streaming(int gate,int entry){
    bee_test.add_bee(gate,entry);
}

/**
 * Clears the board
 * Sets the baord space
 * Creates a new baord and laod it onto the screen
 * */
void Weather::cleanUpForMove(){
    bee_test.step();
    temp_board=(to_string(bee_test.get_score())+"\n"+to_string(bee_test.enteringBees())+"\n"+to_string(bee_test.leavingBees())).c_str();
    ui->label->setText(temp_board);
    clearBoard();
    temp_board = "";
    createBoard();
    loadLabel();
}



void Weather::on_pushButton_clicked()
{
    int randgate= rand () % 5;
    bee_test.add_bee(2,true);
    bee_test.add_bee(randgate,false);
    cleanUpForMove();
}



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animatedbee.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Ensures that the window stays fixed
    ui->display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //Creates the display environment and displays it in the graphics view
    createEnvironment();

}


/**
 * @brief MainWindow::createEnvironment - This method creates a new visual simulation GUI
 */
void MainWindow::createEnvironment(){
    //Create a scene
    animationScene = new QGraphicsScene();
    animationScene->setSceneRect(-250,-250,500,500);



    //Create board to be added to the scene
    AnimationBoard* board = new AnimationBoard(true);
    board->setRect(-250,-250,500,500);

    //add board to the scene
    animationScene->addItem(board);


    QPixmap hivePic(":/images /images/BeehiveEdited5.png");
    hivePic = hivePic.scaled(550,550,Qt::KeepAspectRatio);



    //    QPixmap hivePic(":/images /images/beeHive.png");
    //    hivePic = hivePic.scaled(100,100,Qt::KeepAspectRatio);
    hive = new QGraphicsPixmapItem(hivePic);


    //hive->setPos(-50,-50);

    hive->setPos(-250,-250);
    animationScene->addItem(hive);
    hive->setFlag(QGraphicsItem::ItemIsFocusable);
    hive->setFocus();
    ui->display->setScene(animationScene);
    //ui->display->show();

    //populate the board with bees
    board->populate();


}




void MainWindow::populate(){

    for (int i = 1; i <= 8; i++){
        //AnimatedBee *b = new AnimatedBee(i);
        // setPosition(b);
        //    bees.push_back(b);
    }

}







MainWindow::~MainWindow()
{
   // //cout <<"sound should stop";
    delete ui;
}


//leave methods
QRectF MainWindow::boundingRect(){
    QRectF demo;

    return demo;
}

void MainWindow::paint(QPainter*,const QStyleOptionGraphicsItem*, QWidget){

}

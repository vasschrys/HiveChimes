#include "mainwindowanimate.h"
#include "ui_mainwindowanimate.h"
#include "animatedbee.h"

MainWindowAnimate::MainWindowAnimate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowAnimate)
{
    ui->setupUi(this);
    //Ensures that the window stays fixed
    ui->display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //Creates the display environment and displays it in the graphics view
    createEnvironment();

    //Weather Instatiator
    setLocations();
    parseLocation(California); // this needs to be passed in from GUI eventually
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(findTemp(QNetworkReply*)));
    timer = new QTimer(this);
    getFromWeb();
    connect(timer, SIGNAL(timeout()), this, SLOT(getFromWeb()));
    timer->start(60000); //Check weather updates every minute




}


void MainWindowAnimate::createEnvironment(){
    //Create a scene
    animationScene = new QGraphicsScene();
    animationScene->setSceneRect(-250,-250,500,500);



    //Create board to be added to the scene
    //cout<< "sound " << sound << endl;
    board = new AnimationBoard(sound);
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


    playSound();
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this,SLOT(playSound()));
    timer->start(100);//ev





    //    connect(timer,SIGNAL(timeout()), this,SLOT(populateRT()));
    //    //connect(timer,SIGNAL(timeout()), this,SLOT(playSoundOnScreen()));
    //    timer->start(5000);//every 100ms timeout changes

    //    QTimer *timer1 = new QTimer();
    //    connect(timer,SIGNAL(timeout()), this,SLOT(addBeeRT()));
    //    //connect(timer,SIGNAL(timeout()), this,SLOT(playSoundOnScreen()));
    //    timer1->start(rand() % 100 + 100);//every 100ms timeout changes
    //board->playSoundOnScreen();





    //    QPixmap beeIMG(":/images /images/Indiv_Bee.png");
    //    beeIMG = beeIMG.scaled(50,50,Qt::KeepAspectRatio);
    //    QGraphicsPixmapItem *bee = new QGraphicsPixmapItem(beeIMG);
    //    bee->setPos(-250,-25);
    //    animationScene->addItem(bee);


    //    AnimatedBee *bee = new AnimatedBee();
    //    bee->getBee()->setPos(-250,-25);
    //    animationScene->addItem(bee->getBee());

}

void MainWindowAnimate::addBeeRT(){

    board->addBeeRT();


}


void MainWindowAnimate::populateRT(){

    board->populateRT();


}


void MainWindowAnimate::playSound(){
    if(ui->sound->isChecked()){
        if(board->returnSound()->state() == QMediaPlayer::StoppedState)
            board->returnSound()->play();
        else if (board->returnSound()->isMuted()) {
            board->returnSound()->setMuted(false);
        }
    }
    else {
        if(board->returnSound()->state() == QMediaPlayer::PlayingState)
            board->returnSound()->setMuted(true);
    }

}


MainWindowAnimate::~MainWindowAnimate()
{
    //cout << "close everything";
    board->returnSound()->stop();
    delete ui;
}



void MainWindowAnimate::setSound(bool s){
    sound = s;
}

//gets data from website
void MainWindowAnimate::getFromWeb()
{

    const QUrl myurl = QUrl(url);
    QNetworkRequest request(myurl);
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    manager->get(request);

}

void MainWindowAnimate::quit(){
    this->destroy();
}

void MainWindowAnimate::findTemp(QNetworkReply *reply){
    if(reply->error()){
        qDebug() << reply->errorString();
        return;
    }

    QString str;
    str= reply->readAll();

    content = str.toStdString();
    string tempSummary;
    string temp;


    tempSummary = readBetween("summary\":", ",\"icon\":");
    temp = readBetween(",\"temperature\":", ",\"apparentTemperature\"");
    //temp.append("\xB0");
    temp = temp + string("°F");
    //std:://cout << tempSummary << std::endl;


    //udp message will be sperated by return line
    QString qstring;
    QString qTemp;
    //         newstring = readBetween(
    //             "span class=\"wob_t\" id=\"wob_tm\" style=\"display:inline\">",
    //             "</span><span class=\"wob_t\" id=\"wob_ttm\""
    //         );

    qTemp = QString::fromStdString(temp);



    qstring = QString::fromStdString(tempSummary);
    //ui->cityName->setText(qstring);  //set cityName to Label
    //ui->tempLabel->setText(qTemp);

    ui->temp->setText(qTemp);
    ui->weather->setText(qstring);

}




string MainWindowAnimate::readBetween(string s1, string s2){
    size_t first = content.find(s1) + s1.size();
    size_t second = content.find(s2) - first;
    ////cout <<  content.substr(first, second) << endl;
    return content.substr(first, second);
}



void MainWindowAnimate::printVector(){
    for(int i =0; i<UDPmessage.size(); i++){
        //cout << UDPmessage.at(i) << endl;
    }
}


void MainWindowAnimate::parseLocation(Location location){
    parseLongAndLat(location.latitude, location.longitude);
    ui->cityName->setText(QString::fromStdString(location.city));
}


void MainWindowAnimate::parseLongAndLat(double x, double y){

    string locationURL = string("https://api.darksky.net/forecast/7d4d899326f51981d1d887c0c96f2373/") + to_string(x) + string(",") + to_string(y);
    //cout << locationURL <<endl;
    QString qs = QString::fromStdString(locationURL);
    url = qs; //see the url in the header file to this
}



void MainWindowAnimate:: setLocations(){
    newYork.city = "New York, NY";
    newYork.latitude = 40.7831;
    newYork.longitude = -73.9712;




    California.city = "Davis, CA";
    California.latitude = 38.5449;
    California.longitude = -121.7405;



    Florida.city = "Orlando, FL";
    Florida.longitude = 28.5383;
    Florida.latitude = 81.3792;




}






//leave methods
QRectF MainWindowAnimate::boundingRect(){
    QRectF demo;

    return demo;
}

void MainWindowAnimate::paint(QPainter*,const QStyleOptionGraphicsItem*, QWidget){

}


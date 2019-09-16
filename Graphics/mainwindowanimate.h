#ifndef MAINWINDOWANIMATE_H
#define MAINWINDOWANIMATE_H

#include <QMainWindow>
#include "animatedbee.h"
#include <QGraphicsScene>
#include <vector>
#include <iostream>
#include <QObject>
#include "animationboard.h"



//Weather
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <string>
#include <QTimer>
#include <iostream>
#include <sstream>






using namespace std;


//Structs for locations
struct Location {
    string city;
    double longitude;
    double latitude;
};

namespace Ui {
class MainWindowAnimate;
}

class MainWindowAnimate : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowAnimate(QWidget *parent = nullptr);
    ~MainWindowAnimate();
    void setPosition(AnimatedBee *b);
    void setSound( bool s);

    void createEnvironment();

    QRectF boundingRect();
    void paint(QPainter*, const QStyleOptionGraphicsItem*,QWidget);



    //Weather
    string readBetween(string str1, string str2); //gets string between strings
    void printVector();
    void parseLocation(Location location); // return the url with correct location
    void parseLongAndLat(double x , double y ); //PARSES IN LOGITUDE AND LATITUDE
    void setLocations();
    void quit();

private:
    Ui::MainWindowAnimate *ui;
    QGraphicsScene * animationScene;
    QGraphicsPixmapItem *hive;
    bool sound = false;
    AnimationBoard* board;


    //weather
    Location newYork;
    Location California;
    Location Florida;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QTimer *timer;
    string content; // contains all website information
    QString url;
    vector <string> UDPmessage;


public slots:
    void addBeeRT();
    void populateRT();
    void playSound();



    //Weather slots
    void getFromWeb();
    void findTemp(QNetworkReply *reply);
};

#endif // MAINWINDOWANIMATE_H

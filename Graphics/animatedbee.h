#ifndef ANIMATEDBEE_H
#define ANIMATEDBEE_H


#include <QList>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include <QMediaPlayer>
#include <iostream>



//class AnimatedBee: public QGraphicsPixmapItem

using  namespace std;
class AnimatedBee:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT


public:
    AnimatedBee();
    AnimatedBee(int board, bool type);//type is exit or entry where true is entry
    int getBoard();
    bool getType();
    int getBeeSize();
    void addBee(int i);
    bool isInBounds();

    QGraphicsPixmapItem* getBee();


    //Virtual methods DO NOT DELETE
    QRectF boundingRect();
    void paint(QPainter*,const QStyleOptionGraphicsItem*, QWidget*);


private:
    int board; //there are 10 boards in total
    bool type; //type of board data. False is exit and true is entry
    int beeSize ;//initial size of the bee Object


    //Game window borders
    int topBorder = -250;
    int leftBorder = topBorder;
    int rightBorder = 250;
    int bottomBorder = rightBorder;



    int gate;
    QGraphicsPixmapItem *bee;
    QMediaPlayer *buzz;
    QPixmap beeIMG;

    int count = 1;


public slots:
    void move();



};

#endif // ANIMATEDBEE_H

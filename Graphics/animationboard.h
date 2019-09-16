#ifndef ANIMATIONBOARD_H
#define ANIMATIONBOARD_H

#include "../Data/beegeneration.h"
#include "../Data/datacontainer.h"
#include "../Data/datadecoder.h"
#include <QGraphicsRectItem>
#include "animatedbee.h"
#include <vector>
#include <random>
#include <QObject>
#include <QMediaPlayer>
#include "../RealTimeStream/mainwindowrt.h"

using namespace std;

class AnimationBoard:public QObject, public QGraphicsRectItem

        //class AnimationBoard: public QGraphicsRectItem
{
    Q_OBJECT
public:
    AnimationBoard( bool s);
    void populate();
    void setPosition(AnimatedBee *b);
    void playSoundOnScreen();
    void stopSound();
    QMediaPlayer* returnSound();





private:
    pair<int,int> topL;
    pair<int,int> topR;
    pair<int,int> bottomL;
    pair<int,int> bottomR;
    pair<int,int> mid;
    int beeSize = 50;
    int b=0;
    QMediaPlayer *buzz;


    DataContainer container;
    DataContainer containerRT;

    vector<AnimatedBee*> bees;
    bool sound;
    MainWindowRT *realTime;



public slots:
    void addBee();
    void populateRT();
    void addBeeRT();


};

#endif // ANIMATIONBOARD_H

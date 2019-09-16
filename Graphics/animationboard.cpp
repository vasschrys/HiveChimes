#include "animationboard.h"
#include <QGraphicsScene>

AnimationBoard::AnimationBoard(bool _Sound)
{
    realTime = new MainWindowRT();
    sound = _Sound;
    buzz = new QMediaPlayer();
    buzz->setMedia(QUrl("qrc:/sounds/sound/beesounds.mp3"));


}

/**
 * @brief AnimationBoard::playSoundOnScreen - This method sets the sound to play in a GUI
 */
void AnimationBoard::playSoundOnScreen(){
    // buzz->play();
    if(sound == true){
        //buzz->setVolume(50);
        buzz->play();

    }


}

/**
 * @brief AnimationBoard::returnSound - This method returns the QMedia Player sound
 * @return
 */
QMediaPlayer* AnimationBoard::returnSound(){
    return buzz;
}


/**
 * @brief AnimationBoard::stopSound - This method stops the sound from playing
 */
void AnimationBoard::stopSound(){
  //  //cout << "attempted stop sound";
    buzz->stop();

}

/**
 * @brief AnimationBoard::populateRT - This method populates the DataContainer in real Time
 */
void AnimationBoard::populateRT(){
    DataDecoder d(&containerRT);


    if(realTime->UDPmessage.size() != 0){
        for(int i =0; i<realTime->UDPmessage.size(); i++){
            d.decode(realTime->UDPmessage.at(i));

        }
        realTime->UDPmessage.clear();
    }

    playSoundOnScreen();

}

/**
 * @brief AnimationBoard::populate - This method populates the container not in real-Time
 * (for generating purposes)
 */
void AnimationBoard::populate(){
    DataDecoder d(&container);


    BeeGeneration* BG = new BeeGeneration("0002", 6000);
    for (int i=0;i<100000 ;i++) {
        d.decode(BG->makeBee());
    }
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this,SLOT(addBee()));
    timer->start(rand() % 100 + 250);//every 100ms timeout changes
    playSoundOnScreen();
}

/**
 * @brief AnimationBoard::addBeeRT - This method decodes a udp message and adds a bee in real time
 */
void AnimationBoard::addBeeRT(){
    Data bee=*containerRT.getUdpMessages().at(b);
   // int ran = rand() % 8 + 1;
    if(b<container.getUdpMessages().size()-1)
        b++;
    //int ran = 2;
    AnimatedBee *b = new AnimatedBee(bee.gate,bee.type);
    setPosition(b);


}

/**
 * @brief AnimationBoard::addBee - This method decodes a udp message and adds a bee not in real time
 * (for generating purposes)
 */
void AnimationBoard::addBee(){
    Data bee=*container.getUdpMessages().at(b);
    int ran = rand() % 8 + 1;
    if(b<container.getUdpMessages().size()-1)
        b++;
    //int ran = 2;
    AnimatedBee *b = new AnimatedBee(bee.gate,bee.type);
    setPosition(b);


}

/**
 * @brief AnimationBoard::setPosition - This method sets the position for a bee on the GUI
 * @param b
 */
void AnimationBoard::setPosition(AnimatedBee *b){
    b->getBee()->setPos(-80,-95 );


    //if it is an exit
    if (b->getType() == false){
        if(b->getBoard() == 1){
            b->getBee()->setPos(0,0);
        }
        else if (b->getBoard() == 2){
            b->getBee()->setPos(0,-85);
        }
        else if (b->getBoard() == 3){
            b->getBee()->setPos(-4,-64);
        }
        else if (b->getBoard() == 4){
            b->getBee()->setPos(-35,60);
        }
        else if (b->getBoard() == 5){
            b->getBee()->setPos(-75,57);
        }
        else if (b->getBoard() == 6){
            b->getBee()->setPos(-72,11);
        }
        else if (b->getBoard() == 7){
            b->getBee()->setPos(-76,-33);
        }
        else if (b->getBoard() == 8){
            b->getBee()->setPos(-50,-35);
        }
        else if (b->getBoard() == 9){
            b->getBee()->setPos(-114,40);
        }
        else if (b->getBoard() == 10){
            b->getBee()->setPos(-80,-95);
        }

    }

    //if entry
    else if(b->getType() == true){
        if(b->getBoard() < 7){
            b->getBee()->setPos(250,rand()%500 - 250);
        }
        else {
            b->getBee()->setPos(rand()%500 - 250, -250);
        }

    }

    scene()->addItem(b->getBee());

}

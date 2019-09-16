#include "framework.h"

FrameWork::FrameWork()
{

}

/**
 * @brief FrameWork::createEnvironment - This method creates the background for the Visual GUI
 * @return
 */
QGraphicsScene * FrameWork::createEnvironment(){
    animationScene = new QGraphicsScene();

    QPixmap hivePic(":/images /images/beeHive.png");

    hivePic = hivePic.scaled(100,100,Qt::KeepAspectRatio);
    hive = new QGraphicsPixmapItem(hivePic);


    animationScene->addItem(hive);


    return animationScene;
}

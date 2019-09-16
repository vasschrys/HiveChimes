#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>



class FrameWork
{
public:
    FrameWork();
    QGraphicsScene * createEnvironment(); //creates the environment


private:
    QGraphicsScene *animationScene;
    QGraphicsRectItem *object ;
    QGraphicsPixmapItem *hive;
};

#endif // FRAMEWORK_H

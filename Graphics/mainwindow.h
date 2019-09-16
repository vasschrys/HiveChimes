#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "animatedbee.h"
#include <QGraphicsScene>
#include <vector>
#include <iostream>
#include <QObject>

#include "animationboard.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setPosition(AnimatedBee *b);
    void populate();


    void createEnvironment();






    //To overide void to not delete
    QRectF boundingRect();
    void paint(QPainter*, const QStyleOptionGraphicsItem*,QWidget);


private:
    Ui::MainWindow *ui;
    //FrameWork *frameWork;
    QGraphicsScene * animationScene;
    QGraphicsPixmapItem *hive;

    //vector<AnimatedBee*> bees;




};

#endif // MAINWINDOW_H

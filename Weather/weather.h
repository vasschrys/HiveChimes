#ifndef WEATHER_H
#define WEATHER_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include "../Bee_Visual/bees.h"
#include "../Bee_Visual/engine.h"
#include <thread>
#include <functional>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QImage>


namespace Ui {
class Weather;
}

class Weather : public QMainWindow
{
    Q_OBJECT

public:
    explicit Weather(QWidget *parent = nullptr);
    ~Weather();
    Bees bee_test;
    void cleanUpForMove();
    void streaming(int gate,int entry);
private slots:
    void on_pushButton_clicked();

private:
    void get_Temp();
    QString temp_board;

    QNetworkAccessManager* manager;
    Ui::Weather *ui;
    void draw_board();

    void createBoard();
    void loadLabel();
    void clearBoard();
    //bool QImage::load(const QString &, const char *format = Q_NULLPTR)
    //QImage *bee = new QImage("/User/Jon/qtrepo_grp_01/Weather/Indiv_Bee.png");
};

#endif // WEATHER_H

#ifndef BEES_H
#define BEES_H
#include <QtCharts/QLineSeries>
#include <QtCharts>

#include <QMainWindow>
#include <iostream>
#include <string>
#include "../Data/beegeneration.h"
#include "../Data/datacontainer.h"
#include "../Data/datadecoder.h"
#include "chart.h"
#include "chartview.h"

using namespace  std;
using namespace QtCharts;

namespace Ui {

class Bees;

}

class Bees : public QMainWindow
{
    Q_OBJECT

public:
    explicit Bees(QWidget *parent = nullptr,DataContainer * tool=nullptr);
    map<int,std::pair<int,int>> Timetable(string interval);
    map<int,std::pair<int,int>> Timetable_enter(string interval);
    map<int,std::pair<int,int>> Timetable_exit(string interval);

    ~Bees();


private slots:
    void on_upButton_clicked();

    void on_leftButton_clicked();

    void on_rightButton_clicked();

    void on_downButton_clicked();

    void on_zoomButton_clicked();

    void on_outButton_clicked();

    void on_total_stateChanged(int arg1);

    void on_leaving_stateChanged(int arg1);

    void on_entering_stateChanged(int arg1);

private:
    Ui::Bees *ui;
    QLineSeries *series = new QLineSeries();
    QLineSeries *seriesEnter = new QLineSeries();
    QLineSeries *seriesExit = new QLineSeries();
    DataContainer *beelog;
    int genUsr;
     QChartView *chartView;
    Chart *chart;


    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
};

#endif // BEES_H

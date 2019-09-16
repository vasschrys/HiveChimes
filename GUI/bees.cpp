#include "bees.h"
#include "ui_bees.h"

#include <QtGui/QMouseEvent>
#include <QtWidgets/QRubberBand>
#include <QtCharts/QChartView>


/**
 * @brief Bees::Bees create a graph of a specificied generated data
 * @param parent widget to display the graph
 * @param tool where data to graph is stored
 */
Bees::Bees(QWidget *parent,DataContainer * tool) :
    QMainWindow(parent),
    ui(new Ui::Bees)
{
    ui->setupUi(this);
    beelog=tool;
    int maxX=0;
    int maxY=0;
    //creates series of total bee activity
    map<int,std::pair<int,int>>intervals=Timetable("Hours");
    for (std::map<int,std::pair<int,int>>::iterator it = intervals.begin();it!=intervals.end();++it) {
        //cout<<"X-axis "<<it->second.first<<" Y-axis "<<it->second.second<<endl;
        if (maxX<it->second.first) {
            maxX=it->second.first;
        }
        if (maxY<it->second.second) {
            maxY=it->second.second;
        }
        series->append(it->second.first,it->second.second);
    }
    //cout<<"done all "<<endl;

    //customize total bee activity line
    QPen pen(QRgb(0xFB3640));
    pen.setWidth(2);
    series->setPen(pen);
    ui->total->setStyleSheet("QCheckBox {color: red}");


    //creates series of leaving bee activity
    map<int,std::pair<int,int>>intervals2=Timetable_exit("Hours");
    for (std::map<int,std::pair<int,int>>::iterator it2 = intervals2.begin();it2!=intervals2.end();++it2) {
        //cout<<"X-axis "<<it2->second.first<<" Y-axis "<<it2->second.second<<endl;
        seriesExit->append(it2->second.first,it2->second.second);
    }
    //cout<<"done entry "<<endl;

    //customize leaving bee activity line
    QPen pen2(QRgb(0x3a9b22));
    pen2.setWidth(2);
    seriesExit->setPen(pen2);
    ui->leaving->setStyleSheet("QCheckBox {color: green}");

    //creates series of entering bee activity
    map<int,std::pair<int,int>>intervals3=Timetable_enter("Hours");
    for (std::map<int,std::pair<int,int>>::iterator it3 = intervals3.begin();it3!=intervals3.end();++it3) {
        //cout<<"X-axis "<<it3->second.first<<" Y-axis "<<it3->second.second<<endl;
        seriesEnter->append(it3->second.first,it3->second.second);
    }
    //cout<<"done exit "<<endl;

    //customize entering bee activity line
    QPen pen3(QRgb(0x3972d5));
    pen3.setWidth(2);
    seriesEnter->setPen(pen3);
    ui->entering->setStyleSheet("QCheckBox {color: blue}");

    //create chart to display liens
    chart = new Chart();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(false);


    //customize axes
    axisX->setRange(0, maxX+1);
    axisX->setTickCount((maxX+1)/2);
    axisX->setLabelFormat("%d");
    axisX->setTitleText("time");
    axisY->setRange(0, maxY);
    axisY->setTickCount(10);
    axisY->setLabelFormat("%d");
    axisY->setTitleText("number of bees");

    //customizing design of the chart
    QFont font("Times", 40, QFont::Bold);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle("Bee Activity");
    //customizing background of the chart
    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QRgb(0xDD6E42));
    plotAreaGradient.setColorAt(1.0, QRgb(0xFFC857));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    chart->setPlotAreaBackgroundVisible(true);

    //add the 3 created series to the chart, and attach axes accordingly to all data lines
    chart->setAxisX(axisX,series);
    chart->setAxisY(axisY,series);
    chart->addSeries(series);
    chart->addSeries(seriesExit);
    chart->addSeries(seriesEnter);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    seriesEnter->attachAxis(axisX);
    seriesEnter->attachAxis(axisY);
    seriesExit->attachAxis(axisX);
    seriesExit->attachAxis(axisY);

    //display of chart
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView);
    this->resize(1500, 1000);

    //allow zoom in and out by gestures (alternative from widget buttons)
    this->grabGesture(Qt::PanGesture);
    this->grabGesture(Qt::PinchGesture);




}

/**
 * @brief Bees::Timetable sorts total bee activity by its interval frame
 * @param time interval of each graph points
 * @return  map of total bee activity to time
 */
map<int,std::pair<int,int>> Bees::Timetable(string interval){
    Data entre;
    map<int,std::pair<int,int>>timeslots;
    int times = 0;
    int days=0;
    for (unsigned long var = 0; var < beelog->getUdpMessages().size(); ++var) {
        entre=*beelog->getUdpMessages().at(var);
        if(interval.compare("Hours")==0){
            times=std::stoi(entre.time.substr(0,2))+days*24;
            if(timeslots.size()>0 && timeslots.rbegin()->second.first+1>times && timeslots.rbegin()->second.first-1<times ){
                //cout<<"times "<<times<<" vs. "<<timeslots.rbegin()->second.first<<endl;
                timeslots.rbegin()->second.second=timeslots.rbegin()->second.second+1;
            }else {
                if(timeslots.size()>0){
                    //cout<<"times "<<timeslots.rbegin()->second.first<<" vs.  nob: "<<timeslots.rbegin()->second.second<<endl;
                    if(timeslots.rbegin()->second.first-1>times){
                        days++;
                        times=times+24;
                    }
                }
                timeslots.insert(std::pair<int,std::pair<int,int>>(timeslots.size(),std::pair<int,int>(times,1)));
            }
        }
        //        if(interval.compare("Minutes")==0){
        //            time=std::stoi(entre.time.substr(0,2));
        //            if(timeslots.size()>0)
        //                //cout<<"times "<<entre.time<<" vs. "<<timeslots.rbegin()->first<<endl;
        //            if(timeslots.size()>0 && timeslots.rbegin()->first+1>time){
        //                timeslots.rbegin()->second=timeslots.rbegin()->second+1;
        //                //cout<<"num of bees "<<timeslots.rbegin()->second<<endl;
        //            }else {
        //                timeslots.insert(std::pair<int,int>(time,1));
        //            }
        //        }
        //        if(interval.compare("seconds")==0){
        //            time=std::stoi(entre.time.substr(0,2));
        //            if(timeslots.size()>0)
        //                //cout<<"times "<<entre.time<<" vs. "<<timeslots.rbegin()->first<<endl;
        //            if(timeslots.size()>0 && timeslots.rbegin()->first+1>time){
        //                timeslots.rbegin()->second=timeslots.rbegin()->second+1;
        //                //cout<<"num of bees "<<timeslots.rbegin()->second<<endl;
        //            }else {
        //                timeslots.insert(std::pair<int,int>(time,1));
        //            }
        //        }
    }
    //cout<<times<<endl;
    return timeslots;
}

/**
 * @brief Bees::Timetable_enter sorts entering bee activity by its interval frame
 * @param time interval of each graph points
 * @return  map of entering bee activity to time
 */
map<int,std::pair<int,int>> Bees::Timetable_enter(string interval){
    Data entre;
    map<int,std::pair<int,int>>timeslots;
    int times = 0;
    int days=0;
    for (unsigned long var = 0; var < beelog->getUdpMessages().size(); ++var) {
        entre=*beelog->getUdpMessages().at(var);
        if(entre.type==true){
            entre=*beelog->getUdpMessages().at(var);
            if(interval.compare("Hours")==0){
                times=std::stoi(entre.time.substr(0,2))+days*24;
                if(timeslots.size()>0 && timeslots.rbegin()->second.first+1>times && timeslots.rbegin()->second.first-1<times ){
                    //cout<<"times "<<times<<" vs. "<<timeslots.rbegin()->second.first<<endl;
                    timeslots.rbegin()->second.second=timeslots.rbegin()->second.second+1;
                }else {
                    if(timeslots.size()>0){
                        //cout<<"times "<<timeslots.rbegin()->second.first<<" vs.  nob: "<<timeslots.rbegin()->second.second<<endl;
                        if(timeslots.rbegin()->second.first-1>times){
                            days++;
                            times=times+24;
                        }
                    }
                    timeslots.insert(std::pair<int,std::pair<int,int>>(timeslots.size(),std::pair<int,int>(times,1)));
                }
            }
            //        if(interval.compare("Minutes")==0){
            //            time=std::stoi(entre.time.substr(0,2));
            //            if(timeslots.size()>0)
            //                //cout<<"times "<<entre.time<<" vs. "<<timeslots.rbegin()->first<<endl;
            //            if(timeslots.size()>0 && timeslots.rbegin()->first+1>time){
            //                timeslots.rbegin()->second=timeslots.rbegin()->second+1;
            //                //cout<<"num of bees "<<timeslots.rbegin()->second<<endl;
            //            }else {
            //                timeslots.insert(std::pair<int,int>(time,1));
            //            }
            //        }
            //        if(interval.compare("seconds")==0){
            //            time=std::stoi(entre.time.substr(0,2));
            //            if(timeslots.size()>0)
            //                //cout<<"times "<<entre.time<<" vs. "<<timeslots.rbegin()->first<<endl;
            //            if(timeslots.size()>0 && timeslots.rbegin()->first+1>time){
            //                timeslots.rbegin()->second=timeslots.rbegin()->second+1;
            //                //cout<<"num of bees "<<timeslots.rbegin()->second<<endl;
            //            }else {
            //                timeslots.insert(std::pair<int,int>(time,1));
            //            }
            //        }
        }
    }

    return timeslots;
}

/**
 * @brief Bees::Timetable_exit sorts exiting bee activity by its interval frame
 * @param time interval of each graph points
 * @return  map of exiting bee activity to time
 */
map<int,std::pair<int,int>> Bees::Timetable_exit(string interval){
    Data entre;
    map<int,std::pair<int,int>>timeslots;
    int times = 0;
    int days=0;
    for (unsigned long var = 0; var < beelog->getUdpMessages().size(); ++var) {
        entre=*beelog->getUdpMessages().at(var);
        if(entre.type==false){
            entre=*beelog->getUdpMessages().at(var);
            if(interval.compare("Hours")==0){
                times=std::stoi(entre.time.substr(0,2))+days*24;
                if(timeslots.size()>0 && timeslots.rbegin()->second.first+1>times && timeslots.rbegin()->second.first-1<times ){
                    //cout<<"times "<<times<<" vs. "<<timeslots.rbegin()->second.first<<endl;
                    timeslots.rbegin()->second.second=timeslots.rbegin()->second.second+1;
                }else {
                    if(timeslots.size()>0){
                        //cout<<"times "<<timeslots.rbegin()->second.first<<" vs.  nob: "<<timeslots.rbegin()->second.second<<endl;
                        if(timeslots.rbegin()->second.first-1>times){
                            days++;
                            times=times+24;
                        }
                    }
                    timeslots.insert(std::pair<int,std::pair<int,int>>(timeslots.size(),std::pair<int,int>(times,1)));
                }
            }
            //        if(interval.compare("Minutes")==0){
            //            time=std::stoi(entre.time.substr(0,2));
            //            if(timeslots.size()>0)
            //                //cout<<"times "<<entre.time<<" vs. "<<timeslots.rbegin()->first<<endl;
            //            if(timeslots.size()>0 && timeslots.rbegin()->first+1>time){
            //                timeslots.rbegin()->second=timeslots.rbegin()->second+1;
            //                //cout<<"num of bees "<<timeslots.rbegin()->second<<endl;
            //            }else {
            //                timeslots.insert(std::pair<int,int>(time,1));
            //            }
            //        }
            //        if(interval.compare("seconds")==0){
            //            time=std::stoi(entre.time.substr(0,2));
            //            if(timeslots.size()>0)
            //                //cout<<"times "<<entre.time<<" vs. "<<timeslots.rbegin()->first<<endl;
            //            if(timeslots.size()>0 && timeslots.rbegin()->first+1>time){
            //                timeslots.rbegin()->second=timeslots.rbegin()->second+1;
            //                //cout<<"num of bees "<<timeslots.rbegin()->second<<endl;
            //            }else {
            //                timeslots.insert(std::pair<int,int>(time,1));
            //            }
            //        }
        }
    }
    return timeslots;


}
/**
 * @brief Bees::~Bees deconstructor.  Called when class is deconstructed.
 */
Bees::~Bees()
{
    delete ui;
}


/**
 * @brief Bees::on_upButton_clicked moves the graph's perspective higher
 */
void Bees::on_upButton_clicked()
{
    chart->scroll(0, 10);
}

/**
 * @brief Bees::on_leftButton_clicked moves the graph's perspective to the left
 */
void Bees::on_leftButton_clicked()
{
    //chartView->keyPressEvent(QT::Key_Left);
    chart->scroll(-10, 0);
}

/**
 * @brief Bees::on_rightButton_clicked moves the graph's perspective to the right
 */
void Bees::on_rightButton_clicked()
{
    chart->scroll(10, 0);
}

/**
 * @brief Bees::on_downButton_clicked moves the graph's perspective lower
 */
void Bees::on_downButton_clicked()
{
    chart->scroll(0, -10);
}

/**
 * @brief Bees::on_zoomButton_clicked zooms into the graph for more detail
 */
void Bees::on_zoomButton_clicked()
{
    chart->zoomIn();
}

/**
 * @brief Bees::on_outButton_clicked zooms out the graph for wider view
 */
void Bees::on_outButton_clicked()
{
    chart->zoomOut();
}

/**
 * @brief Bees::on_total_stateChanged allows user to add and remove total bee activity's data line from the graph
 * @param arg1 is the state of checkbox
 */
void Bees::on_total_stateChanged(int arg1)
{
    //checkbox is checked
    if(arg1 == 2){
        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }
    //check box is unchecked
    else{
        chart->removeSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);

    }
}

/**
 * @brief Bees::on_leaving_stateChanged allows user to add and remove leaving bee activity's data line from the graph
 * @param arg1 is the state of checkbox
 */
void Bees::on_leaving_stateChanged(int arg1)
{
    //checkbox is checked
    if(arg1 == 2){
        chart->addSeries(seriesExit);
        seriesExit->attachAxis(axisX);
        seriesExit->attachAxis(axisY);
    }
    //check box is unchecked
    else{
        chart->removeSeries(seriesExit);
        seriesExit->detachAxis(axisX);
        seriesExit->detachAxis(axisY);

    }
}

/**
 * @brief Bees::on_entering_stateChanged allows user to add and remove entering bee activity's data line from the graph
 * @param arg1 is the state of checkbox
 */
void Bees::on_entering_stateChanged(int arg1)
{
    //check box is checked
    if(arg1 == 2){
        chart->addSeries(seriesEnter);
        seriesEnter->attachAxis(axisX);
        seriesEnter->attachAxis(axisY);

    }
    //checkbox is unchecked
    else{
        chart->removeSeries(seriesEnter);
        seriesEnter->detachAxis(axisX);
        seriesEnter->detachAxis(axisY);


    }
}

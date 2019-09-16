#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    setLocations();
    parseLocation(Florida); // this needs to be passed in from GUI eventually
    //parseLongAndLat(42.3601, -71.0589);


    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(findTemp(QNetworkReply*)));
    timer = new QTimer(this);
    getFromWeb();

    connect(timer, SIGNAL(timeout()), this, SLOT(getFromWeb()));

    timer->start(60000); //Check weather updates every minute


}

MainWindow::~MainWindow()
{
    delete ui;
}


//gets data from website
void MainWindow::getFromWeb()
{

    const QUrl myurl = QUrl(url);
    QNetworkRequest request(myurl);
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    manager->get(request);

}

void MainWindow::findTemp(QNetworkReply *reply){
    if(reply->error()){
        qDebug() << reply->errorString();
        return;
    }

     QString str;
     str= reply->readAll();

     content = str.toStdString();
     string tempSummary;
     string temp;


     tempSummary = readBetween("summary\":", ",\"icon\":");
     temp = readBetween(",\"temperature\":", ",\"apparentTemperature\"");
     //temp.append("\xB0");
     temp = temp + string(" Farenheit");
    //std::cout << tempSummary << std::endl;


     //udp message will be sperated by return line
     QString qstring;
     QString qTemp;
//         newstring = readBetween(
//             "span class=\"wob_t\" id=\"wob_tm\" style=\"display:inline\">",
//             "</span><span class=\"wob_t\" id=\"wob_ttm\""
//         );

        qTemp = QString::fromStdString(temp);


      qstring = QString::fromStdString(tempSummary);
      ui->cityName->setText(qstring);  //set cityName to Label
      ui->tempLabel->setText(qTemp);

}

string MainWindow::readBetween(string s1, string s2){
    size_t first = content.find(s1) + s1.size();
    size_t second = content.find(s2) - first;
    //cout <<  content.substr(first, second) << endl;
    return content.substr(first, second);
}

void MainWindow::printVector(){
    for(int i =0; i<UDPmessage.size(); i++){
        cout << UDPmessage.at(i) << endl;
    }
}

void MainWindow::parseLocation(Location location){

    parseLongAndLat(location.longitude, location.latitude);

}

void MainWindow::parseLongAndLat(double x, double y){

    string locationURL = string("https://api.darksky.net/forecast/7d4d899326f51981d1d887c0c96f2373/") + to_string(x) + string(",") + to_string(y);
   cout << locationURL <<endl;
   QString qs = QString::fromStdString(locationURL);

   url = qs; //see the url in the header file to this

}

void MainWindow:: setLocations(){
    newYork.city = "New York, NY";
    newYork.latitude = 40.7831;
    newYork.longitude = -73.9712;




    California.city = "Davis, CA";
    California.longitude = 38.5449;
    California.latitude = -121.7405;



    Florida.city = "Orlando, FL";
    Florida.longitude = 28.5383;
    Florida.latitude = 81.3792;




}



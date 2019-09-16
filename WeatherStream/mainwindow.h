#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <string>
#include <QTimer>
#include <iostream>
#include <sstream>
using namespace  std;
//#include <QPixmap> ///to work with images

struct Location {
    string city;
    double longitude;
    double latitude;
};



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    string readBetween(string str1, string str2); //gets string between strings
    void printVector();

    void parseLocation(Location location); // return the url with correct location
    void parseLongAndLat(double x , double y ); //PARSES IN LOGITUDE AND LATITUDE

    void setLocations();




private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QTimer *timer;
    string content; // contains all website information
    QString url;

    Location newYork;
    Location California;
    Location Florida;



    vector <string> UDPmessage;
private slots:
   void getFromWeb();
   void findTemp(QNetworkReply *reply);


};

#endif // MAINWINDOW_H

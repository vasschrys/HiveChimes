#ifndef MAINWINDOWRT_H
#define MAINWINDOWRT_H


#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <string>
#include <QTimer>
#include <iostream>
#include "../Data/datacontainer.h"
#include "../Data/datadecoder.h"
#include <QMessageBox>
using namespace  std;

namespace Ui {
class MainWindowRT;
}

class MainWindowRT : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowRT(QWidget *parent = nullptr);
    ~MainWindowRT();
    string readBetween(string str1, string str2); //gets string between strings
    vector<string> splitter(string s);
    vector <string> UDPmessage;

private:
    Ui::MainWindowRT *ui;
    DataContainer container;
    DataDecoder *decoder;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QTimer *timer;
    QTimer* timer2;
    string content; // contains all website information
    QString url = "http://tomcollinsresearch.net/research/rpa/fakeudp/fakeudpmgate.html";
    QString translate;
    QString allContent;

    unsigned int i = 0;
private slots:
    void downloadFinished(QNetworkReply *reply);
    void on_pushButton_clicked();
    void checkAlerts();
};

#endif // MAINWINDOWRT_H

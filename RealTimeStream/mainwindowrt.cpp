#include "mainwindowrt.h"
#include "ui_mainwindowrt.h"

MainWindowRT::MainWindowRT(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRT)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_clicked()));

    connect(timer2, SIGNAL(timeout()), this, SLOT(checkAlerts()));

    timer->start(5000); //start timer
    timer2->start(20000);
    on_pushButton_clicked();

    decoder = new DataDecoder(&container);
}

MainWindowRT::~MainWindowRT()
{
    delete ui;
}

/**
 * @brief This method was for testing purposes when initally setting up the class
 */
void MainWindowRT::on_pushButton_clicked()
{

    const QUrl myurl = QUrl(url);
    QNetworkRequest request(myurl);
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    manager->get(request);

}

/**
 * @brief This method takes in the data from the website in realTime, translates it, and places it in a GUI
 * @param reply - A network.
 */
void MainWindowRT::downloadFinished(QNetworkReply *reply){
    if(reply->error()){
        qDebug() << reply->errorString();
        return;
    }

    //Gets the string content from the web page
    QString str;
    string all;
    str= reply->readAll();
    content = str.toStdString();

    content = readBetween("<body>", "</body>");

    string finalUDP;

    //if there is no message at the time
    if (content.size() > 2 ){

        //splits into udp messages
        vector<string> udps = splitter(content);

        //adds each udp message to vector and to string final udp
        for (unsigned int i = 0; i < udps.size();i++) {

            UDPmessage.push_back(udps.at(i));
            finalUDP += udps.at(i) + "\n";
            decoder->decode(udps.at(i));
        }



        //converts final udp to str
        str = QString::fromStdString(finalUDP);

        allContent += str;
        //changes the label
        ui->Label->setText(allContent);  //set URL text to Label

    }


}

/**
 * @brief MainWindowRT::readBetween - This method reads bettwen two stirings, when passiing in the query of a website,
 * we needed to be able to read between syntaxes to distinguish what we wanted to take in from the website.
 * @param s1 string
 * @param s2 string
 * @return string - inbetwwen parameters
 */
string MainWindowRT::readBetween(string s1, string s2){
    size_t first = content.find(s1) + s1.size();
    size_t second = content.find(s2) - first;
    return content.substr(first, second);
}


/**
 * @brief MainWindowRT::splitter - This method splits the string up, according to a delimiter. When reading from a website
 * we found the websites body was still contained in the string we were pulling.
 * @param s string
 * @return string of contnet parsed by delimiters
 */
vector<string> MainWindowRT::splitter(string s){
    vector<string> udps;

    udps.push_back(s.substr(s.find('H') ,s.find("<br/>") - s.find('H') ));

    // //cout << s.substr(s.find('H') ,s.find("<br/>") - s.find('H') );

    ////cout << " ";
    //if string contains more than 1 udp message
    while (s.find("<br/>")  != string::npos){

        //create a string exempting the previous udp message
        s = s.substr(s.find("<br/>")+ 5, s.length() -1);
        udps.push_back(s.substr(s.find('H') ,s.find("<br/>") - s.find('H') ));
    }


    return udps;
}

/**
 * @brief MainWindowRT::checkAlerts - This method cheks for alerts in real time. and displays a message if there is an alert.
 */
void MainWindowRT::checkAlerts(){
    if(decoder->sendExitAlert()== true){
        QMessageBox::warning(this, tr("ERROR MESSAGE"), tr("A Swarm of Bees is Leaving the Hive!"));
        //cout << "Alert True"<< endl;
    }
    if(decoder->sendEntryAlert()==true){
        QMessageBox::warning(this, tr("ERROR MESSAGE"), tr("A Swarm of Bees is Entering the Hive!"));
        //cout << "Alert True"<< endl;
    }
    else{
        //if the alert was false reset the entry and exit data
        decoder->setExitData(0);
        decoder->setEntryData(0);

    }

}


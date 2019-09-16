#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    //initalize vector

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
    timer = new QTimer(this);
    timer2 = new QTimer(this);


    connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_clicked()));

    connect(timer2, SIGNAL(timeout()), this, SLOT(checkAlerts()));

    timer->start(5000); //start timer
    timer2->start(20000);


    decoder = new DataDecoder(&container);


}

MainWindow::~MainWindow()
{
    delete ui;
}


//gets data from website
void MainWindow::on_pushButton_clicked()
{

    const QUrl myurl = QUrl(url);
    QNetworkRequest request(myurl);
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    manager->get(request);

}

void MainWindow::downloadFinished(QNetworkReply *reply){
    if(reply->error()){
        qDebug() << reply->errorString();
        return;
    }




    //Gets the string content from the web page
    QString str;
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


        //changes the label
        ui->Label->setText(str);  //set URL text to Label
        ui->Label->repaint();



        cout << "CONTENT " ;
        cout << ++i;
        cout << "  ";

        cout << content.find('H');
        cout << "  ";

        cout << content.size();

        cout << string("start") + content << endl;


    }





    /*


    str = QString::fromStdString(content);



    ui->Label->setText(str);  //set URL text to Label
    ui->Label->repaint();


    string newstring;
    //udp message will be sperated by return line
    QString qstring;



    //new website with UDp messages
    newstring = readBetween(
                "<body>",
                "</body>"
                );

    cout << "NEW STRINGGGG " + newstring << endl;
  if(newstring != " "){
    vector<string> udps = splitter(newstring, "<br/>");



    for (unsigned int i = 0;i < udps.size();i++) {
        std::cout << udps.at(i) << std::endl;
        decoder->decode(udps.at(i));

        UDPmessage.push_back(udps.at(i));
       qstring = QString::fromStdString(udps.at(i));
       ui->Label->setText(qstring);  //set URL text to Label
       ui->Label->repaint();

    }
    //    std::cout << newstring << std::endl;
    //      decoder->decode(newstring);
    //add UDP message to vector


}

    //printVector(); //print elemetns in the vector




*/
}

string MainWindow::readBetween(string s1, string s2){
    size_t first = content.find(s1) + s1.size();
    size_t second = content.find(s2) - first;
    return content.substr(first, second);
}



vector<string> MainWindow::splitter(string s){
    vector<string> udps;

    udps.push_back(s.substr(s.find('H') ,s.find("<br/>") - s.find('H') ));

    cout << s.substr(s.find('H') ,s.find("<br/>") - s.find('H') );

    cout << " ";


    //if string contains more than 1 udp message
    while (s.find("<br/>")  != string::npos){

        //create a string exempting the previous udp message
        s = s.substr(s.find("<br/>")+ 5, s.length() -1);
        udps.push_back(s.substr(s.find('H') ,s.find("<br/>") - s.find('H') ));
    }








    //    int startIndex = 0;
    //    int  endIndex = 0;
    //    while( (endIndex = s.find(del, startIndex)) < s.size() )
    //    {
    //        std::string val = s.substr(startIndex, endIndex - startIndex);
    //        udps.push_back(val);
    //        startIndex = endIndex + del.size();
    //    }
    //    if(startIndex < s.size())
    //    {
    //        std::string val = s.substr(startIndex);
    //        udps.push_back(val);
    //    }

    return udps;
}


void MainWindow::checkAlerts(){
    if(decoder->sendExitAlert()== true){
          QMessageBox::warning(this, tr("ERROR MESSAGE"), tr("A Swarm of Bees is Leaving the Hive!"));
          //ui->setupUi(this);
          cout << "Alert True"<< endl;
     }
     if(decoder->sendEntryAlert()==true){
           QMessageBox::warning(this, tr("ERROR MESSAGE"), tr("A Swarm of Bees is Entering the Hive!"));
           cout << "Alert True"<< endl;
     }
     else{
           //if the alert was false reset the entry adn exit data
          decoder->setExitData(0);
          decoder->setEntryData(0);
          cout << "made entry/exit ==0 NO WARNING";
     }

    cout << "decoder total" << decoder->totalBees << endl;
    cout << "CHECKED ALERTS"<<endl;

}

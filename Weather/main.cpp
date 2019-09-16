#include "weather.h"
#include <QApplication>
#include <chrono>
#include <QMediaPlayer>
#include "../Data/datadecoder.h"
#include "../Data/datacontainer.h"
#include "../Data/beegeneration.h"

void do_something(Weather* w){
    w->cleanUpForMove();
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Weather *w = new Weather();
    w->show();
    DataContainer container;
    DataDecoder d(&container);
    BeeGeneration* BG = new BeeGeneration("0002", 400, 15);
    for(int i = 0; i < 1000; i++){
        if(container.getUdpMessages().size()>10){
            if(container.getUdpMessages().at(container.getUdpMessages().size()-1)->time>=".15.10.50000"){
                cout << "done"<< endl;
                break;
            }
        }
        d.decode(BG->makeBee());
    }
    int i=0;
    while (true){
        if(i<container.getUdpMessages().size()){
            w->streaming(container.getUdpMessages().at(i)->board,container.getUdpMessages().at(i)->type);
        }
        //auto x = std::chrono::steady_clock::now() +std::chrono::milliseconds(100);
        do_something(w);
        qApp->processEvents();
        //std::this_thread::sleep_until(x);
        i++;
    }
    return a.exec();
}



#include "bees.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    DataContainer container;
    DataDecoder d(&container);
    BeeGeneration* BG = new BeeGeneration("0002", 400);
    //BeeGeneration* BG1 = new BeeGeneration("0009", 400);
    //BeeGeneration* BG2 = new BeeGeneration("0032", 400);

    for(int i = 0; i < 10000; i++){
//        if(container.getUdpMessages().size()>10){
//            if(container.getUdpMessages().at(container.getUdpMessages().size()-1)->time>="161050000"){
//                //cout << "done"<< endl;
//                break;
//            }
//        }
        d.decode(BG->makeBee());
        //d.decode(BG1->makeBee());
        //d.decode(BG2->makeBee());
    }
    QApplication a(argc, argv);
    Bees w(nullptr, &container);
    w.show();

    return a.exec();
}

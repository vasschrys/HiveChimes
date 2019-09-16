//#include "mainwindow.h"
#include <QApplication>
#include "animatedbee.h"
#include "mainwindowanimate.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowAnimate w;
    w.show();


    return a.exec();
}

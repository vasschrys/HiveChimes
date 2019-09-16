//#include "mainwindow.h"
#include <QApplication>
#include "mainwindowrt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowRT w;
    w.show();

    return a.exec();


}

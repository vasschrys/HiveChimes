#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
     // QObject::connect(this, SIGNAL(runs), &a, SLOT(checkAlerts()) )

    return a.exec();
}

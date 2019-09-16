
#ifndef SECONDWINDOWRESEARCHER_H
#define SECONDWINDOWRESEARCHER_H

#include <QDialog>
#include "createmodel.h"
#include "../RealTimeStream/mainwindowrt.h"

namespace Ui {
class secondWindowResearcher;
}

class secondWindowResearcher : public QDialog
{
    Q_OBJECT

public:
    explicit secondWindowResearcher(QWidget *parent = nullptr,QString *hivename=nullptr);
    ~secondWindowResearcher();
    bool viewModel=false;
    bool realTime=false;
    bool playSound=false;
    bool rawData=false;
    bool createModel=false;
    bool getPlaySound();

private slots:
    void on_pushButton_clicked();

private:
    Ui::secondWindowResearcher *ui;
    CreateModel *modelWindow;
    MainWindowRT *realTimeData;
};

#endif // SECONDWINDOWRESEARCHER_H

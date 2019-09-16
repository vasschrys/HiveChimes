#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include "userselectmodel.h"
//#include <QMediaPlayer>
#include "../Graphics/mainwindowanimate.h"
#include <QMediaPlayer>

namespace Ui {
class secondWindow;
}

class secondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondWindow(QWidget *parent = nullptr);
    ~secondWindow();
    bool getPlaySound();
    bool viewModel=false;
    bool realTime=false;
    bool playSound=false;

private slots:
    void on_pushButton_clicked();

private:
    QWidget *mainWindow;
    Ui::secondWindow *ui;
    userSelectModel *userSelect;

   // MainWindowAnimate *animateW;


};

#endif // SECONDWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Data/datacontainer.h"
#include "../Data/datadecoder.h"
#include <QMessageBox>
#include <QObject>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void checkAlerts();
private:
    Ui::MainWindow *ui;
    DataContainer container;
    DataDecoder *decoder;

};

#endif // MAINWINDOW_H

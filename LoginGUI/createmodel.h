#ifndef CREATEMODEL_H
#define CREATEMODEL_H

#include <QDialog>
#include "generatedmodel.h"
#include <string>
#include <iostream>
using namespace std;

namespace Ui {
class CreateModel;
}

class CreateModel : public QDialog
{
    Q_OBJECT

public:
    explicit CreateModel(QWidget *parent = nullptr,QString *hivename=nullptr,Tool*dbtool=nullptr);
    ~CreateModel();
    string times;
    string duration;
    string modeltitle;

    string date;
    string size;
    bool generate=false;

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_dateEdit_dateChanged(const QDate &date);

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_timeEdit_timeChanged(const QTime &time);

    void on_lineEdit_textChanged(const QString &arg1);

    vector<string> checkmodel();

private:
    Ui::CreateModel *ui;
    GeneratedModel *genModel;
    string hiveid;
    Tool* dbtool;
    void hiveSize();

};

#endif // CREATEMODEL_H

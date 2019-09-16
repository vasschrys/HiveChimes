#ifndef USERSELECTMODEL_H
#define USERSELECTMODEL_H

#include <QDialog>
#include <QListWidget>
#include "../Database/dbhivetable.h"
#include "../Database/tool.h"
#include "../Database/dbmodeltable.h"
#include "../Data/datacontainer.h"

using namespace std;

namespace Ui {
class userSelectModel;
}

class userSelectModel : public QDialog
{
    Q_OBJECT

public:
    explicit userSelectModel(QWidget *parent = nullptr,Tool* tool = nullptr,string* tablename=nullptr);
    ~userSelectModel();
    DataContainer *data;
    bool loop=false;
private slots:
    void on_pushButton_clicked();

    void on_ModelList_itemClicked(QListWidgetItem *item);

private:
    Ui::userSelectModel *ui;
    Tool *dbtool;
    DBModelTable *models;
    string modelname;
};

#endif // USERSELECTMODEL_H

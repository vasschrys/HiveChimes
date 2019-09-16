#ifndef DATACONTAINER_H
#define DATACONTAINER_H
#include <vector>
#include <string>
#include "../Database/dbbeelog.h"
#include "../Database/tool.h"
#include "../Database/dbtable.h"
using namespace std;


struct Data{
    string hiveId;
    string date;
    string time;
    int gate;
    int board;
    bool type; //entry or exit with entry being 1 and exit being 0

};

class DataContainer
{
public:
    DataContainer();
    DataContainer(string db_name);
    DataContainer(Tool *tool,string db_name);

    ~DataContainer();
    void addData(Data* d);
    void loadData(Data* d);
    void storeData();
    vector<Data*> getUdpMessages();
    void track_db();


private:
    Tool *dbtool=new Tool("dbtable");
    DBBeeLog *bee_logdb=new DBBeeLog(dbtool,"BEELOG");
    vector<Data*> udpMessages; //recently inputted data

};

#endif // DATACONTAINER_H

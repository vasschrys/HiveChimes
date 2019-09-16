#include <iostream>
#include "tool.h"
#include "dbhivetable.h"
#include "dbbeelog.h"
#include "dbmodeltable.h"
#include <fstream>
#include <string>
using namespace std;

int main()
{
    Tool* dbtool = new Tool("dbtable");
    DBHiveTable *hivedb=new DBHiveTable(dbtool,"HIVEDB");
    DBModelTable *modeldb=new DBModelTable(dbtool,"MODELDB");
    DBBeeLog *bee_logdb=new DBBeeLog(dbtool,"BEELOG");

    hivedb->add_row_h(0,"HD002","shiho","MODELDB");
    modeldb->add_row_m(0,"storing bees","BEELOG");
    bee_logdb->add_row_m(0,1,"A","07/21/1111","00:00:0000","exit");
    bee_logdb->add_row_m(1,4,"A","07/21/1112","00:00:0005","enter");
    bee_logdb->add_row_m(2,4,"A","07/21/1122","00:00:5000","exit");
    bee_logdb->add_row_m(3,4,"A","07/21/1143","00:00:8000","enter");

    std::ofstream fh;
    string filename="../logFile.txt";
    fh.open(filename, std::ofstream::out | std::ofstream::app );
    fh.close();
    std::cout << "appending to : " + filename << std::endl;
    fh.open(filename, std::ofstream::out | std::ios_base::app);
    char** P_rows =hivedb->select_table_h();
    if(P_rows!=nullptr){
        for(int i =0; i<4*(hivedb->size()+1);i=i+1){
            if(i%4==0)
                fh<<"\n";
            fh << P_rows[i]<<" ";
        }
    }
    P_rows =modeldb->select_table_m();
    fh<<"\n";

    if(P_rows!=nullptr){
        for(int i =0; i<3*(modeldb->size()+1);i=i+1){
            if(i%3==0)
                fh<<"\n";
            fh << P_rows[i]<<" ";
        }
    }

    P_rows =bee_logdb->select_table_m();
    fh<<"\n";
    if(P_rows!=nullptr){
        for(int i =0; i<6*(bee_logdb->size()+1);i=i+1){
            if(i%6==0)
                fh<<"\n";
            fh << P_rows[i]<<" ";
        }
    }
    hivedb->select_all();
    modeldb->select_all();
    bee_logdb->select_all();
    return 0;
}

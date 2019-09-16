#include "datacontainer.h"

DataContainer::DataContainer()
{

}

DataContainer::DataContainer(string db_name)
{
    bee_logdb=new DBBeeLog(dbtool,db_name);
    char** P_rows =bee_logdb->select_table_m();
    Data *added;
    if(P_rows!=nullptr){
        for(int i =6; i<6*(bee_logdb->size()+1);i=i+6){
            added=new Data;
            added->board=std::atoi(P_rows[i+1]);
            added->gate=std::atoi(P_rows[i+2]);
            added->date=P_rows[i+3];
            added->time=P_rows[i+4];
            added->type=P_rows[i+5];
            //std::cout <<added->board<< added->gate<<added->date <<added->time << std::endl;
            this->loadData(added);
        }
    }
}

DataContainer::DataContainer(Tool*tool,string db_name)
{
    bee_logdb=new DBBeeLog(tool,db_name);
    char** P_rows =bee_logdb->select_table_m();
    Data *added;
    if(P_rows!=nullptr){
        for(int i =6; i<6*(bee_logdb->size()+1);i=i+6){
            added=new Data;
            added->board=std::atoi(P_rows[i+1]);
            added->gate=std::atoi(P_rows[i+2]);
            added->date=P_rows[i+3];
            added->time=P_rows[i+4];
            added->type=std::atoi(P_rows[i+5]);
            /*std::cout<<"board " <<added->board<<std::endl;
            std::cout <<"gate "<< added->gate<<std::endl;
            std::cout <<"time "<<added->time << std::endl;
            std::cout <<"date "<<added->date << std::endl;
            std::cout <<"Type "<<P_rows[i+5] << std::endl;*/

            this->loadData(added);
        }
    }
}

DataContainer::~DataContainer()
{

}


/**
 * @brief DataContainer::addData - This method adds a row to the database and adds the udp message to a vector
 * @param udpMsg
 */
void DataContainer::addData(Data *udpMsg){
    bee_logdb->add_row_m(int(udpMessages.size()),udpMsg->board,
                         to_string(udpMsg->gate),udpMsg->date,udpMsg->time,to_string(udpMsg->type));
    udpMessages.push_back(udpMsg);
}

/**
 * @brief DataContainer::loadData - This method adds a udp message to the vectro
 * @param udpMsg
 */
void DataContainer::loadData(Data *udpMsg){
    udpMessages.push_back(udpMsg);
}

/**
 * @brief DataContainer::getUdpMessages - This method returns the udp message
 * @return
 */
vector<Data*> DataContainer:: getUdpMessages(){
    return udpMessages;
}

/**
 * @brief DataContainer::storeData - This method stores the data into the database
 */
void DataContainer::storeData(){
    for (unsigned long i=0;i<udpMessages.size();i++) {
        bee_logdb->add_row_m(int(i),udpMessages.at(i)->board,to_string(udpMessages.at(i)->gate),
                             udpMessages.at(i)->date,udpMessages.at(i)->time,to_string(udpMessages.at(i)->type));
    }
}

/**
 * @brief DataContainer::track_db - This method tracks the database when called.
 */
void DataContainer::track_db(){
    bee_logdb->select_all();
}

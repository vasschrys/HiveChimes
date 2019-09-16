#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H
#include "datacontainer.h"

class DataGenerator
{
public:
    DataGenerator();
    void generate(int n);//simple generate method where n is the number of udp messages to be generated
    void generate (int startTime, int endTime);
    void generate (int startTime, int endTime, int weather);


private:
    vector<Data> generated;//

};

#endif // DATAGENERATOR_H

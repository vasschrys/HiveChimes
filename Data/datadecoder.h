#ifndef DATADECODER_H
#define DATADECODER_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "datacontainer.h"


using namespace std;

struct sensorActivity {
    int sensorTime;
    int sensorBoard;
    int sensors;
};

class DataDecoder
{
public:
    DataDecoder( DataContainer *container);
    void decode(string hex);//decodes the string
    string getDecoded();
    string timeDecoder(string s);//take the time info from
    string dateDecoder(string s);
    void activityDecoder(string act);
    void decimalToBinary(int hiveNumber);
     void decimalToBinary2(int hiveNumber);
    void compareSensors(sensorActivity sen);
    void livestream(sensorActivity thisSensor);
    int getPair(int sensorNum);
    bool sendExitAlert();
    bool sendEntryAlert();
    int totalBees;
    void setExitData(int i);
    void setEntryData(int i);

    //getters
    string getHiveID();
    string getDate();
    string getTime();
    string getType();





private:
    string hex;//The string before it is decompiled
    DataContainer *dContainer;
    vector <string> hexArr; //array of data string entries
    int _gate;
    int _board;
    int miliseconds;
    sensorActivity sa;
    vector <sensorActivity> sensorArray;

    Data *d;
    int exitData;
    int entryData;
    int mean;

    //display on GUI
    string _hiveId;
    string _date;
    string _time;
    bool _type;




};

#endif // DATADECODER_H

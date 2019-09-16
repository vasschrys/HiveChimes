#ifndef BEEGENERATION_H
#define BEEGENERATION_H
#include <string>
#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <fstream>
#include <thread>
#include <functional>
#include <cstring>
#include <fstream>
#include <iostream>
#include <time.h>
#include <queue>
#include <string.h>




using namespace std;

//information about the next bee activity waiting. Stored in priority queue
struct nextBee{
    int now[6];
    float m;
    int board;
    int sensor;
} ;

//compares struct of nextBee by time
struct Compare{
    bool operator()(nextBee const& first, nextBee const& second)
    {
        for(int i = 0; i < 6; i ++){
            if(first.now[i] != second.now[i] ){
                return first.now[i] > second.now[i];
            }
        }
        return first.m > second.m  ;
    }
};


class BeeGeneration
{
public:
    //constructors
    BeeGeneration(int size);
    BeeGeneration(string _id, int size);
    BeeGeneration(string _id, int size, int time);

    ~BeeGeneration(); //deconstructor

    float milli, m; //place holder for ms
    priority_queue<nextBee, vector<nextBee>, Compare> nextBees; //stores next few bee activity


    string makeBee();
    void setSeed(unsigned int seed);
    void generateTime();
    void generateTime(int _time);
    void setActivity(int size);
    void update(float ms);
    vector<int> calculate(float ms);
    void generate();
    string generateUDP();
    string anotherActivity(string _udp, int _udpTime[], float _m);
    int findPair(int s);
    int btod(string b);
    void setID(string _id, int size);
    void setID(string _id, int size, int time);
    void setDate(int year,int month, int date);
    int getNextTime(int);
    float getNextM();

private:
    std::default_random_engine generator;   //random generator
    vector<int> lambda;      //stores lambda of the hive's bee activity
    int n;  //number of anticipating bee acitvity left in the hour
    double x;       //number of total bee activity in the hour
    string id;      //id of bee hive
    int time[6];     //latest bee activity to be added into the priory queue
    //vector<int> next;




};

#endif // BEEGENERATION_H

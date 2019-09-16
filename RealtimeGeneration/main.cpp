#include <iostream>
#include "../Data/beegeneration.h"
#include <chrono>
#include <thread>

using namespace std;
//using namespace chrono;

int main()
{
    int time[6];
    int Ti = 7;
    BeeGeneration *BG = new BeeGeneration("001", 2000, Ti);

    BG->generate();
    float m = BG->getNextM();
    for(int i = 0; i<6;i++){
        time[i] = BG->getNextTime(i);
    }
    auto delta = chrono::hours(time[3]) + chrono::minutes(time[4]) + chrono::seconds(time[5]) + chrono::milliseconds((int)m) - chrono::hours(Ti);
    cout << delta.count()<< endl;
    std::this_thread::sleep_for(delta);

    cout << BG->makeBee() << endl;


    for(int i = 0; i< 5; i++){
        delta = chrono::hours(BG->getNextTime(3)) + chrono::minutes(BG->getNextTime(4)) + chrono::seconds(BG->getNextTime(5)) + chrono::milliseconds((int)BG->getNextM());
        delta -= chrono::hours(time[3]) - chrono::minutes(time[4]) - chrono::seconds(time[5]) - chrono::milliseconds((int)m);
        cout << delta.count()<< endl;


        float m = BG->getNextM();
        for(int i = 0; i<6;i++){
            time[i] = BG->getNextTime(i);
        }

        std::this_thread::sleep_for(delta/5);
        cout << BG->makeBee() << endl;
    }
}

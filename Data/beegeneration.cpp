#include "beegeneration.h"


/**
 * @brief BeeGeneration::BeeGeneration constructor that takes in the number of bees in the hive
 * @param size is the number of bees in a hive
 */
BeeGeneration::BeeGeneration(int size)
{
    id = "0000";
    generateTime();
    setActivity(size);
    setSeed(123);

}

/**
 * @brief BeeGeneration::BeeGeneration constructor that takes the a specific HiveId and the number of bees in the hive
 * @param _id is the HiveId
 * @param size is the number of bees in a hive
 */
BeeGeneration::BeeGeneration(string _id, int size){

    id = _id;
    generateTime();
    setActivity(size);
    setSeed(123);

}

/**
 * @brief BeeGeneration::BeeGeneration constructor that takes the a specific HiveId and the number of bees in the hive and a specific starting time in the day
 * @param _id is the HiveId
 * @param size is the number of bees in a hive
 * @param time is the time in hours
 */
BeeGeneration::BeeGeneration(string _id, int size, int time){

    id = _id;
    generateTime(time);
    setActivity(size);
    setSeed(123);

}

/**
 * @brief BeeGeneration::setID sets and restarts new ID for a specfic hive and a new size. Particulary useful for reserching purposes.
 * @param _id is the HiveId
 * @param size is the number of bees in a hive
 */
void BeeGeneration::setID(string _id, int size){

    id = _id;
    generateTime();
    setActivity(size);
    return;
}

/**
 * @brief BeeGeneration::setID sets and restarts new ID for a specfic hive, a new size, and a new starting time.Particulary useful for reserching purposes.
 * @param _id is the HiveId
 * @param size is the number of bees in a hive
 * @param time is the time in hours
 */
void BeeGeneration::setID(string _id, int size, int time){

    id = _id;
    generateTime(time);
    setActivity(size);

    return;
}

/**
 * @brief BeeGeneration::~BeeGeneration is the deconstrucutor which will cleans out previous memory allocation
 */
BeeGeneration::~BeeGeneration()
{
    while(!nextBees.empty()){
        nextBees.pop();
    }

}

void BeeGeneration::setSeed(unsigned int seed){
    generator.seed(seed);
}


/**
 * @brief BeeGeneration::makeBee creates a single bee aka a single UDP message.
 * @return a string which is the UDP message
 */
string BeeGeneration::makeBee()
{

       while(n == 0){ // This while loop checks to see there is reamaning expected bee activity
           std::poisson_distribution<int> poissDistbn(lambda.at(time[3])); //Creates a distuction for that hour based on the activty level
           x = poissDistbn(generator);
           n = x;
           if(x == 0){
               time[3]++;
           }
           if(time[3] == 24){ // This if statement checks to see if a day has elapsed and adjusts the time records acordingly
               time[2] ++;
               time[3] = 0;
           }


       }

       std::exponential_distribution<double> expDistbn(double(x/60)); //Calculates the next expected activity
       //cout << "Hive ID: 23"<< endl;
       while(nextBees.size() < 15){
           float t = expDistbn(generator);
           //cout<< "NEXT BEE" << t*60000<<endl;
           update(t*60000);
           generate();
       }

       n--;
       //cout << "TOP BEE " << nextBees.top().board << " " << nextBees.top().sensor << endl;
       return generateUDP();
}


/**
 * @brief BeeGeneration::pairGenerate generates and formats a UDP message from the priority queue
 * @return string of UDP message
 */
string BeeGeneration::generateUDP(){
    if(nextBees.empty()){
        //cout << "this is why" << endl;
    }

    m = nextBees.top().m;

    string udp;
    udp = "HC" + id + "-D";
    for(int i = 0; i < 6; i++){ //Format of UDP message
        if(i==5 && m == 1000){
            if(nextBees.top().now[i] < 9){
                udp += "0";
            }
            udp += to_string(nextBees.top().now[i]+1);
            m = 0;
            break;
        }
        if(nextBees.top().now[i] < 10){
            udp += "0";
        }
        udp += to_string(nextBees.top().now[i]);

        if(i == 2){
            udp += "T";

        }
        else if(i != 5){
            udp += ".";
        }
    }

    if(m<100){
        udp += "0";
    }
    if(m <10){
        udp += "0";
    }
    udp += to_string((int)m) + "-";


    for(int i =0; i < 10; i++){
        udp+= "B";
        if(i+1 == nextBees.top().board){
            string s = "1";
            for(int i = 1; i < nextBees.top().sensor; i++){
                s += "0";
            }
            udp += to_string(btod(s));
        }
        else{
            udp += "0";
        }
    }

    int udpTime[6];
    for(int i = 0; i < 6; i++){
        udpTime[i] = nextBees.top().now[i];
    }
    if(m == 0){
        udpTime[5] ++;
    }
    float udpm = m;


    nextBees.pop();

    if(!nextBees.empty()){ //Checks to see if gates were triggered at the same time
        for(int i = 0; i < 6; i ++){
            if(nextBees.top().now[i] != udpTime[i]){
                break;
            }
            if(i == 5 && udpm == nextBees.top().m){
                    return anotherActivity(udp, udpTime, m);
            }
        }
    }
    return udp;
}

/**
 * @brief BeeGeneration::anotherActivity is called when there are multiple bee activity occuring in 50ms intervals
 * @param _udp that is already created for one bee activity
 * @param udpTime is the udp's time stored in an array
 * @param _m is the udp's ms time
 * @return updated udp message with one or more activity occuring
 */
string BeeGeneration::anotherActivity(string _udp, int udpTime[], float _m){
    //cout << "another activity?" << endl;
    string udp = "";

    char *cstr = &_udp[0u];
//    char *cstr = new char[_udp.length() + 1];
//    strcpy(cstr, _udp.c_str());
    char * p=std::strtok (cstr,"B");
    udp += p;
    int i = 0;
    string s;
    p = strtok (NULL, "B");
    while (p != NULL)
    {
        udp += "B";
        i++;

        if(i == nextBees.top().board){
            if(std::strncmp( p,"0",1)==0){
                s="1";
                for(int j = 1; j < nextBees.top().sensor; j++){
                    s += "0";
                }
                udp += to_string(btod(s));
            }
            else{
                s = "1";
                for(int k = 1; k < nextBees.top().sensor; k++){
                    s += "0";
                }
                udp += to_string(stoi(p) + btod(s));

            }
        }
        else{
            udp += p;
        }
        p = strtok (NULL, "B");
    }

    nextBees.pop();

    if(nextBees.empty()){ //Checks to see if gates were triggered at the same time
        return udp;
    }
        for(int i = 0; i < 6; i ++){
            if(i == 5 && _m == 0 && nextBees.top().m >950 && nextBees.top().m <1000){
                if((nextBees.top().now[i]-1) == udpTime[i]){
                            //cout << "another activity part 2" << endl;
                    return anotherActivity(udp, udpTime, _m);
                }
                break;
            }
            if(nextBees.top().now[i] != udpTime[i]){
                break;
            }
            if(i == 5){
                if(nextBees.top().m < _m && nextBees.top().m > _m-50){

                    return anotherActivity(udp, udpTime, _m);
                }
            }
        }
    return udp;
}


/**
 * @brief BeeGeneration::Generates a new UDP and stores the pair in a priority queue
 * @param next is the expected time a UDP message specifies
 * @return string which is a UDP message
 */
void BeeGeneration::generate(){

    //FIX THIS
    nextBee bee;
    nextBee pairBee; //Generates random baord
    bee.board = rand() % 10+1;
    pairBee.board = bee.board;

    bee.sensor = rand() % 8+1; //Generates random sensor
    pairBee.sensor = findPair(bee.sensor);

        for(int i = 0; i < 6; i++){
            bee.now[i] = time[i];
        }
        bee.m = nearbyint(milli);
        bee.m += 50-((int)bee.m % 50);

    //cout << "bee: "<< bee.board <<" "<<bee.sensor << endl;
    //cout << "pair bee: "<<pairBee.board<<" "<< pairBee.sensor << endl;

    std::poisson_distribution<int> poissDistbn(450); //Randomly generates the pair UDP message (not in proper format)
    vector<int> elpst =  calculate(poissDistbn(generator));
    pairBee.m = nearbyint(m);
    pairBee.m += 50-((int)pairBee.m % 50);
    for(int i = 0; i < 6; i++){
        pairBee.now[i] = elpst[i];
    }


    nextBees.push(pairBee); //Stores in priority queue


    nextBees.push(bee);




    return;

}

/**
 * @brief BeeGeneration::findPair matches the triggered sensor to the pair gate sensor
 * @param int is the triggered sensor
 * @return is the pair sesnor to the gate
 */
int BeeGeneration::findPair(int s){
    switch(s){
    case 1: {return 8; }
    case 2: {return 7; }
    case 3: {return 6; }
    case 4: {return 5; }
    case 5: {return 4; }
    case 6: {return 3; }
    case 7: {return 2; }
    case 8: {return 1; }
    }
    return 0;
}

/**
 * @brief BeeGeneration::update the last time[] where udp were generated
 * @param ms to be added and updateed appropriately to time[]
 */
void BeeGeneration::update(float ms){

        milli += ms;


        while(milli > 1000){
            milli -=1000;
            time[5]++;
            while(time[5] >60){
                time[5]=0;
                time[4] ++;
            }
            if(time[4] >60){
                time[4]=0;
                time[3]++;
            }
            if(time[3]>24){
                time[3]=0;
                time[2]++;
            }
            if(time[2]>28){
                if(time[1]==2){
                    time[2]=0;
                    time[1]++;
                }
                else if(time[2]>30){
                    if(time[1]==4 ||time[1]==6||time[1]==9||time[1]==11){
                        time[2]=0;
                        time[1]++;
                    }
                }
                if(time[2] > 31){
                    time[2]=0;
                    time[1]++;
                }
            }
            if(time[1]>12){
                time[1]=0;
                time[0]++;
            }

        }


        return;

    }




/**
 * @brief BeeGeneration::calculate which calulates what time it will be if you add the paramter to the current time
 * @param ms takes in milliseconds
 * @return int* points to the calacu array of resulting times, once the param is added
 */
vector<int> BeeGeneration::calculate(float ms){

    //int* ntime=new int;
    vector<int> ntime;
    for(int i = 0; i<6; i++){
        ntime.push_back(time[i]);
    }
    m = milli + ms;


    while(m > 1000){
        m -=1000;
        ntime[5]++;
        while(ntime[5] >60){
            ntime[5]=0;
            ntime[4] ++;
        }
        if(ntime[4] >60){
            ntime[4]=0;
            ntime[3]++;
        }
        if(ntime[3]>24){
            ntime[3]=0;
            ntime[2]++;
        }
        if(ntime[2]>28){
            if(ntime[1]==2){
                ntime[2]=0;
                ntime[1]++;
            }
            else if(ntime[2]>30){
                if(ntime[1]==4 ||ntime[1]==6||ntime[1]==9||ntime[1]==11){
                    ntime[2]=0;
                    ntime[1]++;
                }
            }
            if(ntime[2] > 31){
                ntime[2]=0;
                ntime[1]++;
            }
        }
        if(ntime[1]>12){
            ntime[1]=0;
            ntime[0]++;
        }

    }


    return ntime;

}

/**
 * @brief BeeGeneration::generateTime resets the time to default 01/01/2019 at time 00:00 (Very start of day). Called in constructor.
 */
void BeeGeneration::generateTime(){

    time[0] = 19;
    time[1] = 1;
    time[2] = 1;

    time[3] = 0;
    time[4] = 0;
    time[5] = 0;

    milli = 0;
    n = 0;

    return;

}

/**
 * @brief BeeGeneration::generateTime resets the time to default 01/01/2019 at specfied time. Called in constructor.
 * @param _time which is the hour you want to set the start. (00-24) - 8:00PM = 20
 */
void BeeGeneration::generateTime(int _time){

    time[0] = 19;
    time[1] = 1;
    time[2] = 1;

    time[3] = _time;
    time[4] = 0;
    time[5] = 0;

    milli = 0;
    n = 0;


    return;
}

/**
 * @brief BeeGeneration::setActivity sets the activity levels of a hive based on the HiveSize. Called in the constructor.
 * @param size which is the size of the hive
 */
void BeeGeneration::setActivity(int size){
    double rate = 0;
    for(int i = 0; i<24 ; i++){
        if(i <5){
            rate = 0;
        }
        else if(i == 5){
            rate = 0.1;
        }
        else if(i<11 && i>5){
            rate += 0.1;
        }
        else if(i==11){
            rate = 0.525;
        }
        else if(i>11 && i <15){
            rate = 0.55;
        }
        else if(i == 15){
            rate = 0.35;
        }
        else if(i == 16){
            rate -= 0.1;
        }
        else if(i == 17){
            rate = 0.25;
        }
        else if(i >17 && i <20){
            rate -= 0.1;
        }
        else{
            rate = 0;
        }
        int activity = int (size*rate);
        lambda.push_back(activity);
        //cout <<"shit "<<rate<<endl;
        //cout<<"HA" <<activity<<endl;
    }
}

/**
 * @brief BeeGeneration::btod changes the string in bianry to an integer. Used to generate the UDP represention of sensors.
 * @param b which is the binary representation in a string
 * @return int which is the integer representation of the bianry
 */
int BeeGeneration::btod(string b){
        int num = stoi(b);
        int dec_value = 0;

        int base = 1;

        int temp = num;
        while (temp) {
            int last_digit = temp % 10;
            temp = temp / 10;

            dec_value += last_digit * base;

            base = base * 2;
        }

        return dec_value;
}

/**
 * @brief BeeGeneration::setDate initializes the date of udp generation. Called as needed.
 * @param year specifies initial year to begin generating
 * @param month specifies initial month to begin generating
 * @param date specifies initial date to begin generating
 */
void BeeGeneration::setDate(int year, int month, int date){
    year = year%100;
    time[0] = year;
    time[1] = month;
    time[2] = date;
    return;
}


//vector<int> BeeGeneration::nextUDP(){
//    next.clear();
//    for(int i = 0; i<6;i++){
//        next.push_back(nextBees.top().now[i]);
//    }
//    next.push_back(nextBees.top().m);

//    m = nextBees.top().m;
//    m += 50-((int)nextBees.top().m % 50);

//    string udp;
//    udp = "HC" + id + "-D";
//    for(int i = 0; i < 6; i++){ //Format of UDP message
//        if(i==5 && m == 1000){
//            if(nextBees.top().now[i] < 9){
//                udp += "0";
//            }
//            udp += to_string(nextBees.top().now[i]+1);
//            m = 0;
//            break;
//        }
//        if(nextBees.top().now[i] < 10){
//            udp += "0";
//        }
//        udp += to_string(nextBees.top().now[i]);

//        if(i == 2){
//            udp += "T";

//        }
//        if(i != 5){
//            udp += ".";
//        }
//    }

//    if(m<100){
//        udp += "0";
//    }
//    if(m <10){
//        udp += "0";
//    }

//}


/**
 * @brief BeeGeneration::getNextTime
 * @param i is the index of the time unit of the next bee activity
 * @return next bee activity's specific time unit
 */
int BeeGeneration::getNextTime(int i){
    return nextBees.top().now[i];
}

/**
 * @brief BeeGeneration::getNextM
 * @return return the next bee activity's ms time unit
 */
float BeeGeneration::getNextM(){
    return nextBees.top().m;
}



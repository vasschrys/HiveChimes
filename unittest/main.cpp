#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <map>
#include "gtest/gtest.h"
#include "../Data/beegeneration.h"
#include "../Data/datacontainer.h"
#include "../Data/datadecoder.h"
#include "../Data/datagenerator.h"
//#include "../Database/DBHiveTable.h"

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    FooTest() {
        // You can do set-up work for each test here.
    }

    virtual ~FooTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Foo.

    /** replace with your own **/
    //DBHiveTable t1;
    //DBHiveTable t2;
    BeeGeneration* b1 = new BeeGeneration(2);
    BeeGeneration* b2 = new BeeGeneration(2);
};
//DATABASE TEST SECTION

//TEST(general, GETDATE) {
//    /** replace with your own **/
//    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
//    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
//    ASSERT_EQ(b2->makeBee(), b1->makeBee())
//            << b2->makeBee()
//            << " and "
//            << b1->makeBee()
//            << " should not match!";
//}
//TEST_F(FooTest, UDPGEN) {
//    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
//    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
//    ASSERT_EQ(b2->makeBee(), b1->makeBee())
//            << b2->makeBee()
//            << " and "
//            << b1->makeBee()
//            << " should not match!";
//}
TEST_F(FooTest, RAN) {
    int i=0;
    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
    std::default_random_engine generator;
    int x=100;
    std::exponential_distribution<double> expDistbn(double(600/x)); //Calculates the next expected activity
    //cout << "Hive ID: 23"<< endl;
    while(i < 8){
        b1->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
        b2->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
        i++;
    }
           ASSERT_EQ(b2->milli, b1->milli)
                   << b2->milli
                   << " and "
                   << b1->milli
                   << " should not match!";
}

TEST_F(FooTest, RAN2) {
    int i=0;
    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
    std::default_random_engine generator;
    int x=500;
    std::exponential_distribution<double> expDistbn(double(600/x)); //Calculates the next expected activity
    //cout << "Hive ID: 23"<< endl;
    while(i < 8){
        b1->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
        b2->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
        i++;

    }
           ASSERT_EQ(b2->milli, b1->milli)
                   << b2->milli
                   << " and "
                   << b1->milli
                   << " should not match!";
}
TEST_F(FooTest, RAN3) {
    int i=0;
    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
    std::default_random_engine generator;
    int x=50;
    std::exponential_distribution<double> expDistbn(double(600/x)); //Calculates the next expected activity
    //cout << "Hive ID: 23"<< endl;
    while(i < 8){
        b1->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
        b2->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
        i++;

    }
           ASSERT_EQ(b2->milli, b1->milli)
                   << b2->milli
                   << " and "
                   << b1->milli
                   << " should not match!";
}
TEST_F(FooTest, RAN4) {
    int i=0;
    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
    std::default_random_engine generator;
    int x=3;
    std::exponential_distribution<double> expDistbn(double(600/x)); //Calculates the next expected activity
    //cout << "Hive ID: 23"<< endl;
    while(i < 8){
        b1->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
        b2->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
        i++;

    }
           ASSERT_EQ(b2->milli, b1->milli)
                   << b2->milli
                   << " and "
                   << b1->milli
                   << " should not match!";
}
TEST_F(FooTest, gen1) {
    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
    while(b1->nextBees.size()<8){
    b1->generate();
    }
    while(b2->nextBees.size()<8){
    b2->generate();
    }
    ASSERT_EQ(b2->nextBees.size(), b1->nextBees.size())
            << b2->milli
            << " and "
            << b1->milli
            << " should not match!";
}
TEST_F(FooTest, gen2) {
    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
    b1->generate();
    b2->generate();
    ASSERT_EQ(b2->nextBees.size(), b1->nextBees.size())
            << b2->nextBees.size()
            << " and "
            << b1->nextBees.size()
            << " should not match!";
}

TEST_F(FooTest, udpgen1) {
    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
    std::default_random_engine generator;
    int x=3;
    std::exponential_distribution<double> expDistbn(double(600/x)); //Calculates the next expected activity
    //cout << "Hive ID: 23"<< endl;
        while(b1->nextBees.size()<8){
            b1->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
            b1->generate();
        }
        while(b2->nextBees.size()<8){
            b2->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
            b2->generate();
        }
    ASSERT_EQ(b2->nextBees.size(), b1->nextBees.size())
            << b2->nextBees.size()
            << " and "
            << b1->nextBees.size()
            << " should not match!";
}
TEST_F(FooTest, udpgen2) {
    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
    std::default_random_engine generator;
    int x=3;
    std::exponential_distribution<double> expDistbn(double(600/x)); //Calculates the next expected activity
    //cout << "Hive ID: 23"<< endl;
        while(b1->nextBees.size()<8){
            b1->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
            b1->generate();
        }
        while(b2->nextBees.size()<8){
            b2->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
            b2->generate();
        }
    ASSERT_EQ(b2->nextBees.size(), b1->nextBees.size())
            << b2->nextBees.size()
            << " and "
            << b1->nextBees.size()
            << " should not match!";
}
TEST_F(FooTest, udpgen3) {
    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
    std::default_random_engine generator;
    int x=500;
    std::exponential_distribution<double> expDistbn(double(600/x)); //Calculates the next expected activity
    //cout << "Hive ID: 23"<< endl;
        while(b1->nextBees.size()<8){
            b1->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
            b1->generate();
        }
        while(b2->nextBees.size()<8){
            b2->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
            b2->generate();
        }
    ASSERT_EQ(b2->nextBees.size(), b1->nextBees.size())
            << b2->nextBees.size()
            << " and "
            << b1->nextBees.size()
            << " should not match!";
}
TEST_F(FooTest, udpgen4) {
    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
    std::default_random_engine generator;
    int x=50;
    std::exponential_distribution<double> expDistbn(double(600/x)); //Calculates the next expected activity
    //cout << "Hive ID: 23"<< endl;
        while(b1->nextBees.size()<8){
            b1->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
            b1->generate();
        }
        while(b2->nextBees.size()<8){
            b2->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
            b2->generate();
        }
    ASSERT_EQ(b2->nextBees.size(), b1->nextBees.size())
            << b2->nextBees.size()
            << " and "
            << b1->nextBees.size()
            << " should not match!";
}

TEST_F(FooTest, cal) {
    BeeGeneration* b1 = new BeeGeneration("0002", 400, 15);
    BeeGeneration* b2 = new BeeGeneration("0002", 400, 15);
    std::default_random_engine generator;
    int x=50;
    std::exponential_distribution<double> expDistbn(double(600/x)); //Calculates the next expected activity
    //cout << "Hive ID: 23"<< endl;
        while(b1->nextBees.size()<8){
            b1->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
            b1->generate();
        }
        while(b2->nextBees.size()<8){
            b2->update(6000*expDistbn(generator)); //Calls calcualte which calculates when the next bee will be created
            b2->generate();
        }
    ASSERT_EQ(b2->nextBees.size(), b1->nextBees.size())
            << b2->nextBees.size()
            << " and "
            << b1->nextBees.size()
            << " should not match!";
}
int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

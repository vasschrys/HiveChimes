#include "engine.h"


/**
 * Default Constructor
 * */
engine::engine()
{
    this->num_rows = 30;
    this->num_cols = 30;
    reset_gameboard();
}
/**
 * Constructor for engine class
 * Gameboard array is created
 * */
engine::engine(int r, int c){
    this->num_rows = r;
    this->num_cols= c;
    reset_gameboard();

}


/**
 * Destructor.
 * */
engine::~engine(){
    delete board;
}

/**
 * Method for getting board.
 * */
char** engine::getBoard(){
    return board;
}



/**
 * Method for getting the char of a particular board space.
 * */
char engine::getBrdSpc(int x, int y){
    return board[x][y];
}


bool engine::nullPtrCheck(){
    if(**board != NULL) {
        return false;
    } else {
        return true;
    }
}

//--Like this//

void engine::reset_gameboard(){
    board = new char* [num_rows];
    if (board == nullptr){
        //cout << "Error: nullptr problem";
    }
    else {
        for (int i = 0; i < num_rows; i++)
            board[i] = new char[num_cols];

        for (int i = 0; i < this->num_rows; i++)
            for (int j = 0; j < this->num_cols; j++){
                if(i == 0  || i == (num_rows-1)){
                    board[i][j] = ' ';
                }
                else if(j == 0  || j == (num_cols-1)){
                    board[i][j] = ' ';
                }
                else{
                    board[i][j] = ' ';
                }
            }
    }
}


Bee engine::add_thing(char item, int index){ //Need to finish
    Bee thing;
    thing.row = gate.at(index).first;
    thing.col = gate.at(index).second;
    thing.enter_exit=1;
    thing.gate=findgate(gate.at(index));
    board[thing.row][thing.col] = item;

    return thing;
}

pair<int,int> engine::findgate( pair<int,int> gate){
    int i=num_rows-gate.first;
    int j=num_cols-gate.second;
    int rows1 = rand () % num_rows;
    int cols1 = rand () % num_cols;
    if(i<num_rows/2&& i<j){
        return pair<int,int>(0,cols1);
    }
    else if(i>num_rows/2&&i>j){
        return pair<int,int>(num_rows-1,cols1);

    }
    else if(j<num_cols/2&& j<i){
        return pair<int,int>(rows1,0);

    }
    else if(j>num_cols/2&&j>i){
        return pair<int,int>(rows1,num_cols-1);
    }
    else {
        return pair<int,int>(num_cols-1,num_rows-1);
    }
}

Bee engine::add_random(char item,int index){//Need to finish
    int rows1 = rand () % num_rows;
    int cols1 = rand () % num_cols;
    Bee thing;
    while(board[rows1][cols1] != ' '){ //Only add robots to places with blank spaces //I think I am getting a problem here
        rows1 = rand () % num_rows;
        cols1 = rand () % num_cols;
    }
    board[rows1][cols1] = item;
    thing.col = cols1;
    thing.row = rows1;
    thing.gate=gate.at(index); // This should be the hive location
    return thing;
}

void engine::remove_thing (int row, int col){
    board[row][col] = ' ';
}

char engine::get_thing(int row, int col){
    return board[row][col];
}

int engine::get_num_rows(){
    return this->num_rows;
}

int engine::get_num_cols(){
    return this->num_cols;
}



void engine::printBoard(){
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            //cout << board[i][j];
        }
        //cout << endl;
    }
}



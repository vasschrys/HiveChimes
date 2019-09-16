#ifndef DBModelTable_H
#define DBModelTable_H
#include <iostream>
#include <string>
#include <sqlite3.h>

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "tool.h"
#include "dbtable.h"

class DBModelTable: public DBTable
{
protected:
    std::string sql_select_all;
    std::string sql_update_row;
    std::string sql_select;
    int column = 3;
public:

    DBModelTable();
    DBModelTable(Tool *db, std::string name);

    ~DBModelTable();

    // An overloaded method to generate a new
    // create command for your child class.
    void store_create_sql();

    // An overloaded method to generate a new
    // insert command for your child class.
    virtual void store_add_row_sql();

    bool add_row_m(int id, std::string model_name, std::string entry_vector_table);
    char** select_table_m();
    bool select_all();
};


// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int cb_add_row(void  *data,
               int    argc,
               char **argv,
               char **azColName);


// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int cb_select_all(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

#endif // DBModelTable_H

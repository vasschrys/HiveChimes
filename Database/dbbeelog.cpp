

/*********************************************************************

Copyright (C) 2015 Jeffrey O. Pfaffmann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*********************************************************************/

#include "dbbeelog.h"

// Default constructor.
DBBeeLog::DBBeeLog() {

}

// Constructor for identying the dbtool and table name.
DBBeeLog::DBBeeLog(Tool     *db,
                     std::string name   ) :
    DBTable (db, name)
{

    // Load SQL specific to child class.
    store_add_row_sql();
    store_create_sql();

    // must build table sepparately so new
    // sql can be properly registered
    build_table();
}

DBBeeLog::~DBBeeLog() {

}

void DBBeeLog::store_add_row_sql() {

    sql_template =  "SELECT name ";
    sql_template += "FROM   sqlite_master ";
    sql_template += "WHERE";
    sql_template += "    type = \"table\"";
    sql_template += ";";

}


void DBBeeLog::store_create_sql() {

    //std::cerr << "calling store_create_sql from DBTableEx\n";

    sql_create =  "CREATE TABLE ";
    sql_create += table_name;
    sql_create += " ( ";
    sql_create += " id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  board INT NOT NULL, ";
    sql_create += "  gate TEXT NOT NULL, ";
    sql_create += "  date TEXT NOT NULL, ";
    sql_create += "  time TEXT NOT NULL, ";
    sql_create += "  entry TEXT NOT NULL ";
    sql_create += " );";

}

bool DBBeeLog::add_row_m(int id, int board, std::string gate,std::string date, std::string time, std::string entry_exit) {
    int   retCode = 0;
    char *zErrMsg = 0;

    char tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += table_name;
    sql_add_row += " ( id, board, gate, date, time, entry) ";
    sql_add_row += "VALUES (";

    sprintf(tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sprintf(tempval, "%d", board);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += std::string(gate);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(date);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(time);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(entry_exit);
    sql_add_row += "\" ";

    sql_add_row += " );";

    //std::cout << sql_add_row << std::endl;

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_add_row.c_str(),
                           cb_add_row_b,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

char** DBBeeLog::select_table_m(){
        int   retCode = 0;
        char *zErrMsg = 0;

        char **tempval= 0;
        sql_select  = "SELECT * FROM ";
        sql_select += table_name;
        sql_select += ";";
        std::cout << sql_select << std::endl;
        if(size()<1)
            return nullptr;
        retCode = sqlite3_get_table(curr_db->db_ref(),sql_select.c_str(),
                                    &tempval,&row_cnt,&column,&zErrMsg);
        if( retCode != SQLITE_OK ){

            std::cerr << table_name
                      << " template ::"
                      << std::endl
                      << "SQL error: "
                      << zErrMsg;

            sqlite3_free_table(tempval);
        }

        return tempval;
}

bool DBBeeLog::select_all() {

    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_all.c_str(),
                           cb_select_all_b,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}


int cb_add_row_b(void  *data,
               int    argc,
               char **argv,
               char **azColName)
{



    std::cerr << "cb_add_row being called\n";

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    int i;

    DBBeeLog *obj = (DBBeeLog *) data;

    std::cout << "------------------------------\n";
    std::cout << obj->get_name()
              << std::endl;

    for(i = 0; i < argc; i++){
        std::cout << azColName[i]
                  << " = "
                  <<  (argv[i] ? argv[i] : "NULL")
                  << std::endl;
    }

    return 0;
}


int cb_select_all_b(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName)
{



    std::cerr << "cb_select_all being called\n";

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    int i;

    DBBeeLog *obj = (DBBeeLog *) data;

    std::cout << "------------------------------\n";
    std::cout << obj->get_name()
              << std::endl;

    for(i = 0; i < argc; i++){
        std::cout << azColName[i]
                  << " = "
                  <<  (argv[i] ? std::string(argv[i]) : "NULL")
                  << std::endl;
    }

    return 0;
}

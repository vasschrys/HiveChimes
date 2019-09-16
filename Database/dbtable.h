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

#ifndef DBTABLE_H
#define DBTABLE_H

#include <iostream>
#include <string>
#include <sqlite3.h>

#include <sys/stat.h>
#include <sys/types.h>

#include "tool.h"

/**
 * @brief The DBTable class
 *
 * This class provides the parent functionality for a class that
 * will be implementing the basic table functionality.  The
 * virutal methods also provide examples of the type of
 * functionality that needs to be implemented in the inherited
 * class.
 *
 * There are also several functions that are not part of the
 * class, but are required by the sqlite software function.  The
 * are generally named cb or "call back", indicating that they
 * will be called by the sqlite software to provide functionality
 * back to your code.
 *
 * A called to sqlite_exec is detailed in the exist method, which
 * is how these classes interfaces to the SQLite tool.
 */

class DBTable {

protected:

    // name of the table where data will be stored
    std::string table_name;

    // reference to the global database tool
    Tool *curr_db;

    // sql for retrieving table names from the database
    std::string sql_template;

    // default sql for determining if table exists
    std::string sql_exist;

    // default sql for creating associated table
    std::string sql_create;

    // default sql for dropping the associated table
    std::string sql_drop;

    // default sql for determining number of rows in the table
    std::string sql_size;
    std::string sql_add_row;

    // internal flag for storing the result of the last exists request
    bool table_exists;

    // internal value for storing the result of the last size request
    int  row_cnt;

public:

    // constructors
    DBTable();
    DBTable(Tool *db, std::string name);

    // destructor
    virtual ~DBTable();

    // method for rebuilding the table regardless of existance
    void build_table();

    // These methods are for storing the base sql commands, these methods
    // can be overloaded for storing your own sql command and should
    // be used as examples for enhancing the functionality of a
    // child class inheriting from this parent class.
    virtual void store_template_sql();

    virtual void store_exist_sql();
    virtual void store_create_sql();
    virtual void store_drop_sql();
    virtual void store_size_sql();

    int dbtemplate();

    // methods for performing the activities
    bool exist(); // used
    bool create(); // used
    bool drop();
    int  size();

    std::string get_name();

    void set_exists()      {table_exists = true; }
    void unset_exists()    {table_exists = false;}
    void set_size(int cnt) {row_cnt      = cnt;  }

};

// Functions for providing callback functionality to the
// sqlite database repository.  See exists method and callback
// for details about parameters.
int cb_template(void *data, int argc, char **argv, char **azColName);
int cb_exist   (void *data, int argc, char **argv, char **azColName);
int cb_create  (void *data, int argc, char **argv, char **azColName);
int cb_drop    (void *data, int argc, char **argv, char **azColName);
int cb_load    (void *data, int argc, char **argv, char **azColName);
int cb_store   (void *data, int argc, char **argv, char **azColName);
int cb_size    (void *data, int argc, char **argv, char **azColName);

#endif // DBTABLE_H

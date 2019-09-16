#ifndef TOOL_H
#define TOOL_H


#include <iostream>
#include <string>
#include <sqlite3.h>

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <set>
#include <map>

class Tool
{
private:

    /// Name of the database.
    std::string db_name;

    /// Location of the database in the file structure.
    std::string db_location;

    sqlite3 *curr_db;

public:

    // Constructor that if called will cause the program to exit
    // indicating that more information should be provided.
    Tool();

    // Constructors for loading a database file in the current
    // working directory.
    Tool(std::string name);
    Tool(const char* name);

    // Constructors for loading a database file in a specified
    // directory location.
    Tool(std::string location, std::string name);
    Tool(const char* location, const char* name);

    // Destructor that will cause the database to be closed storing
    // the updated contents of the sqlite file.
    ~Tool();

    // Used to manually open the file, and called by each of the
    // constructors.
    int open_db();

    // prints state of database
    void print(std::ostream &sout);

    // provides a state check to determine if database is available
    bool db_open() { return curr_db ? true : false; }

    // Returns a pointer to the current database, only
    // used when absolutely necessary!
    sqlite3* db_ref()  { return curr_db; }
};

#endif // TOOL_H

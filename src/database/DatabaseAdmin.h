#ifndef DB_ADMIN
#define DB_ADMIN

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <sqlite3.h>

// #include "DatabaseConnection.h"

namespace Database {
    class DatabaseAdmin {
    public:
        DatabaseAdmin();
        DatabaseAdmin(const std::string& path);
        ~DatabaseAdmin() {
            sqlite3_close(db);
            delete dbPath; 
        }
        std::string checkDatabaseExists(std::string dbName = DATABASE_FILE);
        std::string initTable(std::string query, 
                            std::string dbName = DATABASE_FILE);
        void deleteUserTable(void);

    private:
        static std::string DATABASE_FILE;
        const char* dbPath;
        sqlite3* db;
        const static std::string USER_TABLE_STATEMENT;
        const static std::string LOGIN_ATTEMPTS_TABLE_STATEMENT;
    };
}


#endif //DB_ADMIN
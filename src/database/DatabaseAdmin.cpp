

#include "DatabaseAdmin.h"

// initialise database upon first call

namespace Database {

    std::string DatabaseAdmin::DATABASE_FILE = "secure-login.db";
    const std::string DatabaseAdmin::USER_TABLE_STATEMENT = 
                            "CREATE TABLE IF NOT EXISTS users ("
                            "username int NOT NULL, "
                            "password VARCHAR(100), "
                            "PRIMARY KEY (username) " 
                            ");";
    // table to track login attempts
    const std::string DatabaseAdmin::LOGIN_ATTEMPTS_TABLE_STATEMENT = 
                            "CREATE TABLE login_attempts ("
                            "userID INT PRIMARY KEY AUTO_INCREMENT,"
                            "username VARCHAR(255),"
                            "attemptTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                            "success BOOLEAN"
                            ");";



    DatabaseAdmin::DatabaseAdmin() {

        if (checkDatabaseExists() == "SUCCESS") {
            std::cout << initTable(USER_TABLE_STATEMENT) << std::endl;
            initTable(LOGIN_ATTEMPTS_TABLE_STATEMENT);
        }
    }

    DatabaseAdmin::DatabaseAdmin(const std::string& path) {

        dbPath = path.c_str();
        checkDatabaseExists();
    }

    std::string DatabaseAdmin::checkDatabaseExists(std::string dbName){
        
        // check file before attempting to make a connection

        std::ostringstream valid;

        sqlite3 *db = nullptr;
        int rc = sqlite3_open(dbName.c_str(), &db); // db initialised to file

        if (rc) {
            valid << "Can't open database: " << sqlite3_errmsg(db);
        } 
        else {
            valid << "SUCCESS";
        }

        if (db) {
            sqlite3_close(db);
            db = nullptr;
        }
        return valid.str();
    }

    std::string DatabaseAdmin::initTable(std::string query, 
                                        std::string dbName) {

        std::ostringstream valid;
        char *zErrMsg = 0;
        sqlite3 *db = nullptr;
        int rc = sqlite3_open(dbName.c_str(), &db); // db initialised to file

        rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);

        if( rc != SQLITE_OK ){
            valid << " SQL error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        } else {
            valid << "Table created successfully " << std::endl;
        }
        sqlite3_close(db);

        return valid.str();
    }

    void DatabaseAdmin::deleteUserTable(void) {

        std::cout << "FIXME" << std::endl;

        std::string query = "DROP TABLE IF EXISTS users";

    }

}


#include "DatabaseAdmin.h"

// initialise database upon first call

namespace Database {


    DatabaseAdmin::DatabaseAdmin(std::string path) {

        // path to be provided by the controller

        dbPath = path;

        if (!checkDatabaseExists()) {
            // initialise tables here
            initUserTable();
        }


    }

    bool DatabaseAdmin::checkDatabaseExists (void){
        // check file before attempting to make a connection
        std::ifstream file(dbPath);
        return file.good();
    }

    void DatabaseAdmin::initUserTable(void) {
        std::cout << "FIXME" << std::endl;
        try { 

            auto connection = std::make_unique<Connection::DBConnection>();

            std::string query = "CREATE TABLE IF NOT EXISTS users ("
                                "username int NOT NULL, "
                                "password VARCHAR(100), "
                                "PRIMARY KEY (username) " 
                                ");";

            auto stmt = std::make_unique<sql::Statement>(
                                    connection->getConnection()->createStatement());
            stmt->execute(query);

        }
        catch (const sql::SQLException& e) {
            std::cout << "FIXME" << std::endl;
            // TODO: error to throw
            throw ;
        }

    }

    void DatabaseAdmin::deleteUserTable(void) {

        std::cout << "FIXME" << std::endl;

        try { 

            auto connection = std::make_unique<Connection::DBConnection>();

            std::string query = "DROP TABLE IF EXISTS users";

            auto stmt = std::make_unique<sql::Statement>(
                            connection->getConnection()->createStatement());
            stmt->execute(query);


        }
        catch (const sql::SQLException& e) {
            std::cout << "FIXME" << std::endl;
            // error to throw
            throw ;
        }
    }

}
#include <iostream>
#include <memory>

#include "DatabaseConnection.h"

// initialise database upon first call

namespace Database { 

    void generateDatabase(void) {

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
            // error to throw
            throw ;
        }

    }

    void deleteDatabase(void) {

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
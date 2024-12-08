#ifndef DB_CONNECTION
#define DB_CONNECTION

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>
#include <memory>

namespace Database {
    namespace Connection {
        class DBConnection {

        public:
            DBConnection(const std::string user = "root", const std::string password = "");
            ~DBConnection(void);
            sql::Connection* getConnection(void) {
                return con;
            }

        private:
            std::unique_ptr<sql::mysql::MySQL_Driver> driver;
            sql::Connection* con;
            static const std::string HOST;
            static const std::string DB_NAME; 

        };
    }
}


#endif //DB_CONNECTION
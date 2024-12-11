#include "DatabaseConnection.h"


namespace Database {

const std::string DBConnection::HOST = "tcp://127.0.0.1:3306";
const std::string DBConnection::DB_NAME = "Authentication_Model";

DBConnection::DBConnection(const std::string user, const std::string password) {
    try {
        driver = std::make_unique<sql::mysql::MySQL_Driver>
                        (sql::mysql::get_mysql_driver_instance());
        con = driver->connect(HOST, user, password);
        con->setSchema(DB_NAME);
    } 
    catch (const sql::SQLException& e) { // can change the exception
        throw std::runtime_error(e.what());
    }

}


DBConnection::~DBConnection(void) {
    // connection established upon class call
    // con will not be empty
    if (con) {
        delete con;
    }
}

}
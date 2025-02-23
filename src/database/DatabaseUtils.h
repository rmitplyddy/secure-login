#ifndef DATABASE_UTILS
#define DATABASE_UTILS


#include "PasswordHasher.h"
#include "src/UserDTO.h"



// #include "DatabaseConnection.h"

// #include "auth/AuthModel.h"
// #include "user/UserModel.h"
#include <sqlite3.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <QDebug>



namespace Database {

    inline constexpr const char* DATABASE_FILE = "secure-login.db";

    std::string checkDatabaseExists(const std::string& dbName = DATABASE_FILE);
    std::string initUserTable(const std::string& dbName = DATABASE_FILE);
    std::string validateUser(const std::unique_ptr<UserDTO>& auth, 
                            const std::string& dbname = DATABASE_FILE);
    std::string createUser(const std::unique_ptr<UserDTO>& newUser, 
                            const std::string& dbname = DATABASE_FILE);

    
}

#endif // DATABASE_UTILS
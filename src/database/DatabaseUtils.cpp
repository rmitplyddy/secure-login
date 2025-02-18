#include "DatabaseUtils.h"


// update namespace for modules with c++ v20



namespace Database {

   
    static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        
        for(int i = 0; i < argc; i++) {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }


    std::string checkDatabaseExists(const std::string& dbName){
            
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


    std::string initUserTable(const std::string& dbName) {

        std::ostringstream valid;

        char *zErrMsg = 0;
        sqlite3 *db = nullptr;
        int rc = sqlite3_open(dbName.c_str(), &db); // db initialised to file


        std::string query = "CREATE TABLE IF NOT EXISTS users ("
                            "username int NOT NULL, "
                            "password VARCHAR(100), "
                            "PRIMARY KEY (username) " 
                            ");";

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

    std::string validateUser(const std::unique_ptr<UserDTO>& auth) {

        // try {
            // std::unique_ptr<Connection::DBConnection> connection = 
            //                 std::make_unique<Connection::DBConnection>();
            // connection->getConnection();

            // any necessary encryption conversion types here for validation
            std::string hashedPW = ""; //FIXME

            std::string query = "SELECT username "\ 
                                "FROM users, "\ 
                                "WHERE username = ? AND"\
                                "WHERE password = ?";

            // std::unique_ptr<sql::PreparedStatement> 
            //             prepstmt(connection->getConnection()->prepareStatement(query));

            // prepstmt->setString(1, auth->getUsername());
            // prepstmt->setString(2, hashedPW);

            
            // std::unique_ptr<sql::ResultSet> 
            //                         result(prepstmt->executeQuery(query));

            // while (result->next()) {


            // }
            

        // }
        // catch (const sql::SQLException& e) {
        //     std::cout << "FIXME" << std::endl;
        //     throw ; //DBexception

        // }
        // catch (std::runtime_error& e) { // exceptions for DBconnection
        //     std::cout << "FIXME" << std::endl;
        //     throw ; // log of error

        // }
    }


    std::string createUser(const std::unique_ptr<UserDTO>& newUser, 
                        const std::string& dbName) {

        std::ostringstream qryResult;

        // use password hashing functionality
        // auto passwordHasher = std::make_unique<PasswordHasher>();
        // std::string hashedPassword = passwordHasher->hash(
        //                                         newUser->getPassword());
        sqlite3 *db = nullptr;
        sqlite3_open(dbName.c_str(), &db); // db initialised to file

        std::string query = 
                        "INSERT INTO users (username, password) VALUES (?, ?) ";

        sqlite3_stmt* stmt = nullptr;
        sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr);

        sqlite3_bind_text(stmt, 1, newUser->username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, newUser->hashedPassword.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            qryResult << "User  " << newUser->username << " created successfully";
        }
        else {
            qryResult << "Execution failed";
        }

        sqlite3_finalize(stmt); // deconstruct prepared statement
        sqlite3_close(db);

        return qryResult.str();
    }


    std::string editUser(std::string username, std::string password) {
        std::cout << "FIXME" << std::endl;

    }


    void deleteUser(/* User user*/) {
        std::cout << "FIXME" << std::endl;
    }

}
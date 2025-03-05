#include "DatabaseUtils.h"


// update namespace for modules with c++ v20


namespace Database {

   
    // static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        
    //     for(int i = 0; i < argc; i++) {
    //         printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    //     }
    //     printf("\n");
    //     return 0;
    // }


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

    // userID should be randomised

    // std::string initUserTable(const std::string& dbName, std::string query) {

    //     std::ostringstream valid;

    //     sqlite3 *db = nullptr;
    //     int rc = sqlite3_open(dbName.c_str(), &db); // db initialised to file


    //     // std::string query = "CREATE TABLE IF NOT EXISTS users ("
    //     //                     "userID int PRIMARY KEY, "
    //     //                     "username VARCHAR(255) UNIQUE, "
    //     //                     "password VARCHAR(255), "
    //     //                     "PRIMARY KEY (username) " 
    //     //                     ");";

    //     char *zErrMsg = 0;
    //     rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);

    //     if (rc != SQLITE_OK) {
    //         valid << " SQL error: " << zErrMsg << std::endl;
    //         sqlite3_free(zErrMsg);
    //     } else {
    //         valid << "Table created successfully " << std::endl;
    //     }
    //     sqlite3_close(db);

    //     return valid.str();
    // }

/*
Pseudo code for authentication:

-- using the "quick exit approach"

        password_hash=HASH(password)
        IS_VALID=LOOKUP_CREDENTIALS_IN_STORE(username, password_hash)
        IF NOT IS_VALID THEN
        RETURN Error("Invalid Username or Password!")
        ENDIF


checking both username and password at the same time to avoid time-based 
attacks.


*/




// Track a failed attempt
// INSERT INTO login_attempts (username, success) VALUES ('user1', FALSE);

// Check failed attempts for a user (e.g., within the last 30 minutes)
// SELECT COUNT(*) FROM login_attempts
// WHERE username = 'user1'
// AND success = FALSE
// AND attempt_time > NOW() - INTERVAL 30 MINUTE;


    int checkLoginAttempts(const std::unique_ptr<UserDTO>& user, 
                            const std::string& dbName) {

        sqlite3 *db = nullptr;
        sqlite3_open(dbName.c_str(), &db); // db initialised to file

        std::string query = "SELECT COUNT(*) FROM login_attempts"
                            "WHERE username = ? "
                            "AND attemp_time > ( "
                                "SELECT MAX(attempt_time) FROM login_attempts " 
                                "WHERE username = ? AND success = TRUE"
                            ");";
        int failedAttempts = 0;
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, query.c_str(), 
                                -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, user->username.c_str(), -1, 
                                    SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, user->username.c_str(), -1, 
                                    SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                failedAttempts = sqlite3_column_int(stmt, 0);
            }
        }
        return failedAttempts;
    }


    void incrementLoginAttempt(const std::unique_ptr<UserDTO>& user, 
                                sqlite3* db, std::string success) {

        std::string loginAttemptQuery = 
                                    "INSERT INTO login_attempts (username, success) " \
                                    "VALUES (?, ?);";

        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, loginAttemptQuery.c_str(), 
                                -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, user->username.c_str(), -1, 
                                        SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, success.c_str(), -1, 
                                        SQLITE_TRANSIENT);
            sqlite3_step(stmt);
        }
        
    }

    std::string validateUser(const std::unique_ptr<UserDTO>& auth, 
                                            const std::string& dbName) {

        sqlite3 *db = nullptr;
        sqlite3_open(dbName.c_str(), &db); // db initialised to file

        std::ostringstream result("");

        std::string query = "SELECT password " \
                            "FROM users " \
                            "WHERE username = ?;";

        sqlite3_stmt* stmt = nullptr;

        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        
        if (rc != SQLITE_OK) {
            qDebug() << query;
            result << "SQL error: check prepared statement ";
        }
        else {
            qDebug() << auth->username;
            if (sqlite3_bind_text(stmt, 1, auth->username.c_str(), -1, 
                                    SQLITE_TRANSIENT) != SQLITE_OK) {
                result << "SQL error: check binding error ";
            }
            else {
                if (sqlite3_step(stmt) == SQLITE_ROW) {
                    const unsigned char* sqlresult = 
                                sqlite3_column_text(stmt, 0);
                    std::string storedPassword = 
                        std::string(reinterpret_cast<const char*>(sqlresult));
                    std::string enteredPW = auth->password;
                    if (verifyPassword(enteredPW, storedPassword)) {
                        incrementLoginAttempt(auth, db, "TRUE");
                        result << "SUCCESS";
                    }
                    else {
                        incrementLoginAttempt(auth, db, "FALSE");
                    }
                }
            }
        }
        sqlite3_finalize(stmt); // deconstruct prepared statement
        sqlite3_close(db);
        return result.str();
    }


    std::string createUser(const std::unique_ptr<UserDTO>& newUser, 
                        const std::string& dbName) {

        std::ostringstream qryResult("");

        auto passwordHashed = hashAndSaltPassword(newUser->password);

        sqlite3 *db = nullptr;
        sqlite3_open(dbName.c_str(), &db); // db initialised to file

        std::string query = 
                        "INSERT INTO users (username, password) VALUES (?, ?) ";
        sqlite3_stmt* stmt = nullptr;
        sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr);

        sqlite3_bind_text(stmt, 1, newUser->username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, passwordHashed.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            qryResult << "User  " << newUser->username << 
                                                " created successfully";
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
        std::cout << username << " " << password << std::endl;
        return "FIXME";
    }


    void deleteUser(/* User user*/) {
        std::cout << "FIXME" << std::endl;
    }

}
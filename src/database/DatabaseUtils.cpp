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

    // bool garbleDeGarble(std::string ePW) {
    //     qDebug() << "garble garble";
    //     qDebug() << ePW;
    // }


    std::string initUserTable(const std::string& dbName) {

        std::ostringstream valid;

        sqlite3 *db = nullptr;
        int rc = sqlite3_open(dbName.c_str(), &db); // db initialised to file


        std::string query = "CREATE TABLE IF NOT EXISTS users ("
                            "username int NOT NULL, "
                            "password VARCHAR(100), "
                            "PRIMARY KEY (username) " 
                            ");";

        char *zErrMsg = 0;
        rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);

        if (rc != SQLITE_OK) {
            valid << " SQL error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        } else {
            valid << "Table created successfully " << std::endl;
        }
        sqlite3_close(db);

        return valid.str();
    }

    std::string validateUser(const std::unique_ptr<UserDTO>& auth, 
                                            const std::string& dbName) {
        // const std::string enteredPW = "frank";
        // const std::string foundPW = "frank";

        // garbleDeGarble(enteredPW);
        // qDebug() << "adfad";
        // verifyPassword(enteredPW, foundPW);



        sqlite3 *db = nullptr;
        sqlite3_open(dbName.c_str(), &db); // db initialised to file

        std::ostringstream result("");

        std::string query = "SELECT password "\ 
                            "FROM users "\ 
                            "WHERE username = ? ;";

        sqlite3_stmt* stmt = nullptr;

        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        
        if (rc != SQLITE_OK) {
            qDebug() << "prepared failure";
            result << "SQL error: check binding error ";
        }
        else {
            
            rc = sqlite3_bind_text(stmt, 1, auth->username.c_str(), -1, SQLITE_TRANSIENT);

            if (rc != SQLITE_OK) {
                qDebug() << "binding failure";
                result << "SQL error: check binding error ";
            }
            else {
                if (sqlite3_step(stmt) == SQLITE_ROW) {
                    const unsigned char* sqlresult = 
                                sqlite3_column_text(stmt, 0);
                    std::string storedPassword = 
                        std::string(reinterpret_cast<const char*>(sqlresult));
                    qDebug() << "stored:" << QString::fromStdString(storedPassword); 
                    qDebug() << "entered:" << QString::fromStdString(auth->password); 
                    std::string enteredPW = auth->password;
                    if (verifyPassword(enteredPW, storedPassword)) {
                        qDebug() << "success";
                        result << "SUCCESS";
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

        qDebug() << "before the hash";
        auto passwordHashed = hashAndSaltPassword(newUser->password);
        qDebug() << "after the hash";
        // use password hashing functionality
        // auto passwordHasher = std::make_unique<PasswordHasher>();
        // std::string password = passwordHasher->hash(
        //                                         newUser->getPassword());
        sqlite3 *db = nullptr;
        sqlite3_open(dbName.c_str(), &db); // db initialised to file

        std::string query = 
                        "INSERT INTO users (username, password) VALUES (?, ?) ";
        sqlite3_stmt* stmt = nullptr;
        sqlite3_prepare_v2(db, query.c_str(), query.length(), &stmt, nullptr);

        sqlite3_bind_text(stmt, 1, newUser->username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, passwordHashed.c_str(), -1, SQLITE_STATIC);

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
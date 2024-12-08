#include "DatabaseUtils.h"


// update namespace for modules with c++ v20



namespace Database {


    std::string validateUser(const std::shared_ptr<Model::Authenticator> auth) {

        try {
            std::unique_ptr<Connection::DBConnection> connection = 
                            std::make_unique<Connection::DBConnection>();
            connection->getConnection();

            // any necessary encryption conversion types here for validation
            std::string hashedPW = ""; //FIXME

            std::string query = "SELECT username "\ 
                                "FROM usr_table, "\ 
                                "WHERE username = ? AND"\
                                "WHERE password = ?";

            std::unique_ptr<sql::PreparedStatement> 
                        prepstmt(connection->getConnection()->prepareStatement(query));

            prepstmt->setString(1, auth->getUsername());
            prepstmt->setString(2, hashedPW);

            
            std::unique_ptr<sql::ResultSet> 
                                    result(prepstmt->executeQuery(query));

            // while (result->next()) {


            // }
            

        }
        catch (const sql::SQLException& e) {
            std::cout << "FIXME" << std::endl;
            throw ; //DBexception

        }
        catch (std::runtime_error& e) { // exceptions for DBconnection
            std::cout << "FIXME" << std::endl;
            throw ; // log of error

        }
    }


    std::string Database::createUser(std::unique_ptr<Model::User> newUser) {

        std::string qryResult = ""; // change to bool?

        try {
            std::unique_ptr<Connection::DBConnection> connection = 
                            std::make_unique<Connection::DBConnection>();
            connection->getConnection();

            // use password hashing functionality
            auto passwordHasher = std::make_unique<PasswordHasher>();
            std::string hashedPassword = passwordHasher->hash(
                                                    newUser->getPassword());

            // std::string query = "SELECT " + username + " FROM usr_table "\ 
            //                 "WHERE password = ?";

            std::string query = 
                            "INSERT INTO (username, password) VALUES (?, ?) ";
            std::unique_ptr<sql::PreparedStatement> 
                        preparedStmt(connection->getConnection()
                                    ->prepareStatement(query));

            preparedStmt->setString(1, newUser->getUsername());
            preparedStmt->setString(2, hashedPassword);

            preparedStmt->executeUpdate();

            qryResult = "SUCCESS";

        }
        catch (sql::SQLException& e) {

            // username exists

        }
        catch (std::runtime_error& e) {
            // connection error
            // log and close program


        }

        return qryResult;
    }


    std::string editUser(std::string username, std::string password) {
        std::cout << "FIXME" << std::endl;

    }


    void deleteUser(/* User user*/) {
        std::cout << "FIXME" << std::endl;
    }

}
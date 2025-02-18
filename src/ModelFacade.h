#ifndef MODEL_FACADE
#define MODEL_FACADE

// #include "user/UserModel.h"
// #include "auth/AuthModel.h"
#include "auth/AuthModel.h"
#include "UserDTO.h"
// #include "database/DatabaseAdmin.h"
#include "database/DatabaseUtils.h"


#include <string>

namespace Model {
    class ModelFacade {
        
        public:
            ModelFacade() {
                Database::checkDatabaseExists();
                Database::initUserTable();
                // Database::DatabaseAdmin(); // intialise database
                // dbAdmin = std::make_unique<Database::DatabaseAdmin>();
                authModel = nullptr;
                // authModel = nullptr;
            }
            bool createUser(std::string, std::string);
            bool authenticateUser(std::string, std::string);
            bool editUser(std::string username, std::string password);
        
        private:
            std::unique_ptr<Authenticator> authModel;
            // std::unique_ptr<Database::DatabaseAdmin> dbAdmin;

    };
}


#endif //MODEL_FACADE
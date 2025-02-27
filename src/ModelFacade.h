#ifndef MODEL_FACADE
#define MODEL_FACADE


#include "auth/AuthModel.h"
#include "UserDTO.h"
#include "database/DatabaseUtils.h"


#include <string>

namespace Model {
    class ModelFacade {
        
        public:
            ModelFacade() {
                Database::checkDatabaseExists();
                Database::initUserTable();
                authModel = nullptr;
            }

            void checkPasswordStrength(const std::unique_ptr<UserDTO>& userDTO);
            bool createUser(const std::unique_ptr<UserDTO>& userDTO);
            bool authenticateUser(const std::unique_ptr<UserDTO>& userDTO);
            bool editUser(std::unique_ptr<UserDTO> userDTO);
        
        private:
            std::unique_ptr<Authenticator> authModel;
            int loginAttempts;

            const static int MAX_LOGIN_ATTEMPTS;

    };
}


#endif //MODEL_FACADE
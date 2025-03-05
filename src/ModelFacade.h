#ifndef MODEL_FACADE
#define MODEL_FACADE

#include "UserDTO.h"
#include "database/DatabaseAdmin.h"
#include "database/DatabaseUtils.h"


#include <string>

namespace Model {
    class ModelFacade {
        
        public:
            ModelFacade() {
                auto database = std::make_unique<Database::DatabaseAdmin>();
            }

            void checkPasswordStrength(
                                const std::unique_ptr<UserDTO>& userDTO);
            bool createUser(const std::unique_ptr<UserDTO>& userDTO);
            std::string authenticateUser(
                                const std::unique_ptr<UserDTO>& userDTO);
            bool editUser(std::unique_ptr<UserDTO> userDTO);
        
        private:
            int loginAttempts;
            const static int MAX_LOGIN_ATTEMPTS;

    };
}


#endif //MODEL_FACADE
#ifndef MODEL_FACADE
#define MODEL_FACADE

#include "user/UserModel.h"
#include "auth/AuthModel.h"


namespace Model {
    class ModelFacade {

        bool createUser(std::string, std::string);
        bool authenticateUser(std::string, std::string);
        bool editUser(std::string username, std::string password);
    };
}


#endif //MODEL_FACADE
#include "ModelFacade.h"




namespace Model {


    bool ModelFacade::createUser(const std::unique_ptr<UserDTO>& userDTO) {

        // create user model - validation checks
        // decide on where to put password logic checking
        // can encapsulate logic in deeper model / here.

        // check OWASP guidelines (ie min characters)
        // acceptable characters for hashing

        std::string result = Database::createUser(userDTO);

        bool success = false;
        if (result == "SUCCESS") {
            success = true;
        }

        return success;
    }


    bool ModelFacade::authenticateUser(const std::unique_ptr<UserDTO>& userDTO) {

        bool success = false;

        std::string result = Database::validateUser(userDTO);

        if (result == "SUCCESS") {
            success = true;
        }

        return success;
    }

    bool ModelFacade::editUser(std::unique_ptr<UserDTO> userDTO){ 
        std::cout << "FIXME" << userDTO->username << userDTO->password << std::endl;
        // FIXME
        return -1;

    }



}
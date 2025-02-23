#include "ModelFacade.h"




namespace Model {

    bool ModelFacade::createUser(std::string username, std::string password) {

        // create user model - validation checks
        // decide on where to put password logic checking
        // can encapsulate logic in deeper model / here.

        // check OWASP guidelines (ie min characters)
        // acceptable characters for hashing

        auto userDTO = std::make_unique<UserDTO>(username, password);

        std::string result = Database::createUser(userDTO);

        std::cout << "here" << std::endl;
        std::cout << result << std::endl;


        bool success = false;
        if (result == "SUCCESS") {
            success = true;
        }

        return success;
    }


    bool ModelFacade::authenticateUser(std::string username, std::string password) {

        bool success = false;

        std::cout << "authenticate user here" << std::endl;

        

        // encapsulate entered details as a DTO
        auto userDTO = std::make_unique<UserDTO>(username, password);

        std::cout << username << " " << password << std::endl;
        std::string result = Database::validateUser(userDTO);

        if (result == "SUCCESS") {
            success = true;
        }

        return success;
    }

    bool ModelFacade::editUser(std::string username, std::string password){ 
        std::cout << "FIXME" << username << password << std::endl;
        // FIXME
        return -1;

    }



}
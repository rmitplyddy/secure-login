#include "ModelFacade.h"




namespace Model {

    bool ModelFacade::createUser(std::string username, std::string password) {


        auto userDTO = std::make_unique<UserDTO>(username, password);

        std::string result = Database::createUser(userDTO);

        std::cout << "here" << std::endl;
        std::cout << result << std::endl;
        // create user model - validation checks
        // decide on where to put password logic checking
        // can encapsulate logic in deeper model / here.

        // check OWASP guidelines (ie min characters)
        // acceptable characters for hashing

        // auto newUser = std::make_unique<User>();

        // try {
        //     newUser->setUsername(username);
        //     newUser->setPassword(password);
        //     // Database::createUser(std::move(newUser));

        // } catch (const std::exception& e) {
        //     throw std::exception();
        // }
    }


    bool ModelFacade::authenticateUser(std::string username, std::string password) {

        // check whether "authenticator" is required.
        // perhaps only take string
        // should decouple functions from each other
        bool success = false;

        std::cout << "authenticate user here" << std::endl;

        std::cout << username << " " << password << std::endl;

        // encapsulate entered details as a DTO
        // authModel = std::make_unique<Authenticator>(username, password);

        auto auth = std::make_unique<Authenticator>(username, password);
        // if (authModel == nullptr) {
        //     authModel = std::make_unique<Authenticator>();
        // }

        // delete authModel;
        // if (Database::validateUser(std::move(authModel)) == "SUCCESS") {
        //     auto user = std::make_shared<User>(username); 
        //     success = true;
        // }
        // return success;
    }

    bool ModelFacade::editUser(std::string username, std::string password){ 
        std::cout << "FIXME" << std::endl;
        // FIXME
        return -1;

    }



}
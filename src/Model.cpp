#include "ModelFacade.h"
#include "auth/AuthModel.h"
#include "database/DatabaseUtils.h"

namespace Model {

bool ModelFacade::createUser(std::string username, std::string password) {

    // create user model - validation checks
    // decide on where to put password logic checking
    // can encapsulate logic in deeper model / here.

    // check OWASP guidelines (ie min characters)
    // acceptable characters for hashing

    auto newUser = std::make_unique<User>();

    try {
        newUser->setUsername(username);
        newUser->setPassword(password);
        Database::createUser(std::move(newUser));

    } catch (const std::exception& e) {
        throw std::exception();
    }
}


bool ModelFacade::authenticateUser(std::string username, std::string password) {

    // check whether "authenticator" is required.
    // perhaps only take string
    // should decouple functions from each other
    bool success = false;
    auto auth = std::make_shared<Authenticator>(username, password);
    if (Database::validateUser(auth) == "SUCCESS") {
        auto user = std::make_shared<User>(username); 
        success = true;
    }
    return success;
}

bool ModelFacade::editUser(std::string username, std::string password){ 
    std::cout << "FIXME" << std::endl;
    // FIXME
    return -1;

}



}
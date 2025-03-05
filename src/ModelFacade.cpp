#include "ModelFacade.h"




namespace Model {

const int ModelFacade::MAX_LOGIN_ATTEMPTS = 3;

// Using any of the authentication mechanisms (login, password reset, or 
// password recovery), an application must respond with a generic error message 
// regardless of whether:

// The user ID or password was incorrect.
// The account does not exist.
// The account is locked or disabled.


// Login Throttling
// Login Throttling is a protocol used to prevent an attacker from making 
// too many attempts at guessing a password through normal interactive means, 
// it includes:
        // account lockout
        // CAPTCHA
        // security questions and memorable words (consider ease of 
                                            // predictability)


// Maximum number of attempts.


// Enable logging and monitoring of authentication functions 
// to detect attacks/failures on a real-time basis

// Ensure that all failures are logged and reviewed
// Ensure that all password failures are logged and reviewed
// Ensure that all account lockouts are logged and reviewed



    std::string ModelFacade::authenticateUser(const std::unique_ptr<UserDTO>& userDTO) {

        std::string result = "";

        if (Database::checkLoginAttempts(userDTO) < 3) {
            result = Database::validateUser(userDTO);
        }
        else {
            // error message to return to user
            result = "Invalid Username or Password";
        }
        return result;
    }


void ModelFacade::checkPasswordStrength(const std::unique_ptr<UserDTO>& userDTO) {

        // password length - 12-16 characters
        // no forced special characters - focus on length
        // block known breached passwords (consider API)
        // deny common passwords (ie "password", "123...", "qwerty")
        // context specific passwords
        // password changes are not enforced

        // MFA supported - consider Authy or another app
        // temporary lock on account where too many failed attempts occurred
                // include a safe unlock process
        // enforce reset for breach mechanism


        int pwSize = userDTO->password.size();
        if (pwSize < 8) {
            throw std::exception(); // change as req
        }
        
        int specialChar = 0;
        int intCount = 0;
        int capsCount = 0;

        for (int i = 0; i < pwSize; ++i) {
            if (userDTO->password.at(i)) { // logic for special char
                specialChar += 1;
            }
            else if (userDTO->password.at(i)) { // count int
                intCount += 1;
            }
            else if (userDTO->password.at(i)) {  
                capsCount += 1;
            }
        }

        if (specialChar == 0 || intCount == 0 || capsCount == 0) {
            throw std::exception();
        }
        if (specialChar + intCount + capsCount == pwSize ) {
            throw std::exception();
        }

        // this->password = password;
    }



// The account registration feature should also be taken into consideration, 
// and the same approach of a generic error message can be applied regarding 
// the case in which the user exists.

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



    bool ModelFacade::editUser(std::unique_ptr<UserDTO> userDTO){ 
        std::cout << "FIXME" << userDTO->username << userDTO->password << std::endl;
        // FIXME
        return -1;

    }



}
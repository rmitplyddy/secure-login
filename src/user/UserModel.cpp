#include "UserModel.h"

namespace Model
{
    void User::setUsername(std::string name) {

        // username security parameters

        // username exists??
        // email for username

    }

    void User::setPassword(std::string password) {

        int pwSize = password.size();
        if (pwSize < 8) {
            throw std::exception(); // change as req
        }

        int specialChar = 0;
        int intCount = 0;
        int capsCount = 0;
        for (int i = 0; i < pwSize; ++i) {
            if (password.at(i)) { // logic for special char
                specialChar += 1;
            }
            else if (password.at(i)) { // count int
                intCount += 1;
            }
            else if (password.at(i)) {  
                capsCount += 1;
            }
        }

        if (specialChar == 0 || intCount == 0 || capsCount == 0) {
            throw std::exception();
        }
        if (specialChar + intCount + capsCount == pwSize ) {
            throw std::exception();
        }

        this->password = password;
    }

} // namespace Model
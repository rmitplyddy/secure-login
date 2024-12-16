#ifndef AUTHENTICATION_M
#define AUTHENTICATION_M

#include <string>
#include <iostream>

#include "database/DatabaseAdmin.h"
#include "database/DatabaseUtils.h"

// namespace Model {
    class AuthenticatorModel {

    public:
        AuthenticatorModel(std::string uname, std::string pw);
        std::string getUsername() const { return username; }
        std::string getPassword() const { return password; }
        void displayAuthenticator(void) {
            std::cout << username << " " << password << std::endl;
        }

    private:
        std::string username;
        std::string password;
    };
// }

#endif // AUTHENTICATION_M
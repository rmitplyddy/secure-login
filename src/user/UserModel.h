#ifndef USERMODEL
#define USERMODEL

#include <string>
#include <iostream>


namespace Model {
    class User {

    public: // protected - needs to be managed differently
        User() {}
        User(std::string name) : username(name){}
        std::string getUsername(void) const { return username; }
        std::string getPassword(void) const { return password; }
        void display(void) {
            std::cout << " username: " << username << std::endl;
        }
        void setUsername(std::string name);
        void setPassword(std::string password);

    private:
        std::string username;
        std::string password;
    };
}


#endif //USERMODEL
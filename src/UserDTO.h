#ifndef USERDTO
#define USERDTO

#include <string>

struct UserDTO {

    // data transportation object for users

    const std::string username;
    const std::string password;

    UserDTO(std::string name, std::string pw) : username(name), 
                                            password(pw) {};
    UserDTO(std::string name) : username(name) {};
};

#endif
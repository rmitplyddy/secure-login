#ifndef USERDTO
#define USERDTO

#include <string>

struct UserDTO {

    const std::string username;
    const std::string password;

    UserDTO(std::string name, std::string pw) : username(name), 
                                            password(pw) {};
};



// class UserDTO {

// private:
//     std::string username;
//     std::string hashedPassword;

// public:
//     UserDTO(std::string name, std::string pw) : username(name), 
//                                             hashedPassword(pw) {};
//     std::string getUsername() { return username; };
//     std::string getHashedPassword() { return hashedPassword; };


// };

#endif
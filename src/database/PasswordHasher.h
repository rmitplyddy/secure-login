#ifndef PASSWORD_HASH
#define PASSWORD_HASH

#include <memory>
#include <iostream>
#include <argon2.h>
#include <random>
#include <QDebug>
#include <sstream>

// #include <openssl/rand.h>
#include <string>

// class PasswordHasher {
// public:
//     PasswordHasher(int time = 2, int memory = 16, int parallel = 1, 
//                     size_t salt = 16) :
//                     timeCost(time), memoryCost(memory),  parallelism(parallel) ,
//                     saltSize(salt) {};
//     std::string hashAndSaltPassword(const std::string& string);
//     // void generateSalt(std::shared_ptr<unsigned char> salt);
//     void generateSalt(unsigned char* salt);
//     std::string base64Encoder(const unsigned char* binaryData, size_t size);

// private:
//     int timeCost;
//     int memoryCost;
//     int parallelism;
//     size_t saltSize;

// };

std::string hashAndSaltPassword(const std::string& string);
// void generateSalt(std::shared_ptr<unsigned char> salt);
void generateSalt(unsigned char* salt, int& saltSize);
std::string base64Encoder(const unsigned char* binaryData, size_t size);
bool verifyPassword(const std::string& enteredPassword, const std::string& storedEncoded);



#endif // PASSWORD_HASH



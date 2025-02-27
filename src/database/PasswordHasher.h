#ifndef PASSWORD_HASH
#define PASSWORD_HASH

#include <memory>
#include <iostream>
#include <argon2.h>
#include <random>
#include <QDebug>
#include <sstream>

#include <string>

std::string hashAndSaltPassword(const std::string& string);
void generateSalt(unsigned char* salt, int& saltSize);
std::string base64Encoder(const unsigned char* binaryData, 
                            size_t size);
bool verifyPassword(const std::string& enteredPassword, 
                    const std::string& storedEncoded);

#endif // PASSWORD_HASH



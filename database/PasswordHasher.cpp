#include "PasswordHasher.h"
#include <memory>
#include <iostream>

// https://en.wikipedia.org/wiki/Argon2
// https://crypto.stackexchange.com/questions/39249/argon2-output-length-and-parameter-storage

// void PasswordHasher::generateSalt(std::shared_ptr<unsigned char> salt) {

void PasswordHasher::generateSalt(unsigned char* salt) {
    //FIXME
    std::cout << "FIXME" << std::endl;
}


std::string PasswordHasher::base64Encoder(const unsigned char* binaryData, size_t size) {
    // raw binary to be converted back to ASCII
        //FIXME
    std::cout << "FIXME" << std::endl;
}

std::string PasswordHasher::hash(const std::string& password) {

    // auto salt = std::make_shared<unsigned char>(saltSize);
    unsigned char salt[saltSize];
    generateSalt(salt);

    // maximum allowable hash out - consider making this a member var
    size_t hashSize = ARGON2_MAX_OUTLEN; 
    unsigned char hash[hashSize];

    int result = argon2d_hash_raw(timeCost, memoryCost, parallelism, password.c_str(),
                                password.size(), salt, saltSize, hash, hashSize);

    if (result != ARGON2_OK) {
        throw std::runtime_error("Error: Could not hash password");
    }

    std::string saltBase = base64Encoder(salt, saltSize);
    std::string hashBase = base64Encoder(hash, hashSize);

    std::string encoded = "$argon2d$v=19$m=" + std::to_string(memoryCost) 
                        + "t=" + std::to_string(timeCost) + ",p=" 
                        + std::to_string(parallelism) + "$" 
                        + saltBase + "$" + hashBase;

    delete salt;
    delete hash;

    return encoded;
}
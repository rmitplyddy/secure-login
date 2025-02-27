#include "PasswordHasher.h"

// https://en.wikipedia.org/wiki/Argon2
// https://crypto.stackexchange.com/questions/39249/argon2-output-length-and-parameter-storage


std::string base64Encoder(const unsigned char* binaryData, size_t size) {
    
    std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    std::string encodedString;
    int val = 0, valb = -6;

    for (size_t i = 0; i < size; ++i) {
        val = (val << 8) + binaryData[i];
        valb += 8;

        while (valb >= 0) {
            encodedString.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    
    // Handle any remaining bits and padding
    if (valb > -6) {
        encodedString.push_back(
                            base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    }
    
    // Add padding if necessary
    while (encodedString.size() % 4) {
        encodedString.push_back('=');
    }
    
    return encodedString;
}



bool base64Decoder(const std::string& encoded, unsigned char* output, 
                    size_t& outSize) {
    std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int val = 0, valb = -8;
    size_t index = 0;

    for (char c : encoded) {
        if (c == '=') break;  // Ignore padding

        size_t pos = base64_chars.find(c);
        if (pos == std::string::npos) return false;

        val = (val << 6) + pos;
        valb += 6;

        if (valb >= 0) {
            output[index++] = (val >> valb) & 0xFF;
            valb -= 8;
        }
    }
    outSize = index;
    return true;
}



void generateSalt(unsigned char* salt, int& saltSize) {

    // Random number generator
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    // Distribution for 1 byte (0-255)
    std::uniform_int_distribution<int> dis(0, 255);  
            
    
    for (int i = 0; i < saltSize; ++i) {
        // Generate a random byte
        salt[i] = dis(gen);  
    }
}

std::string hashAndSaltPassword(const std::string& password) {

    std::ostringstream returnResult("");

    int saltSize = 16;

    unsigned char salt[saltSize];


    generateSalt(salt, saltSize);

    qDebug() << salt;
    
    // maximum allowable hash out - consider making this a member var
    // 32 bytes = 256 bits
    // increase size of hash for stronger pw security
    // reduce size for performance

    int hashSize = 32; // represent strong default for pw hashing
    unsigned char hash[hashSize];


    int timeCost = 2;
    int memoryCost = 16;
    int parallelism = 1;


    int result = argon2d_hash_raw(timeCost, memoryCost, parallelism, 
                                  password.c_str(), password.size(),
                                  salt, saltSize, hash, hashSize);

    if (result != ARGON2_OK) {
        returnResult << "Error: Could not hash password";
    }
    else {

        std::string saltBase = base64Encoder(salt, saltSize);
        std::string hashBase = base64Encoder(hash, hashSize);

        // argon2 string encoding format:
        // https://github.com/P-H-C/phc-string-format/blob/master/phc-sf-spec.md
        std::string encoded = "$argon2d$v=19$m=" + std::to_string(memoryCost) 
                            + "t=" + std::to_string(timeCost) 
                            + ",p=" + std::to_string(parallelism) 
                            + "$" + saltBase 
                            + "$" + hashBase;

        returnResult << encoded;
    }

    return returnResult.str();
}




bool verifyPassword(const std::string& enteredPassword, 
                    const std::string& storedEncoded) {

    // 1: Parse the stored encoded string
    size_t paramPos = storedEncoded.find("$m=");
    size_t saltPos = storedEncoded.find("$", paramPos + 1);
    size_t hashPos = storedEncoded.find("$", saltPos + 1);

    std::string params = storedEncoded.substr(paramPos + 1, 
                                                saltPos - paramPos - 1);
    std::string saltBase64 = storedEncoded.substr(saltPos + 1, 
                                                hashPos - saltPos - 1);
    std::string hashBase64 = storedEncoded.substr(hashPos + 1);

    // // Extract parameters
    int memoryCost = std::stoi(params.substr(params.find("m=") + 2, 
                                params.find(",t=") - 2));
    int timeCost = std::stoi(params.substr(params.find("t=") + 2, 
                                params.find(",p=") - 2));
    int parallelism = std::stoi(params.substr(params.find("p=") + 2));

    // 2: Decode the salt and stored hash
    unsigned char salt[16];
    size_t saltSize = 0;
    base64Decoder(saltBase64, salt, saltSize);

    unsigned char storedHash[32];
    size_t hashSize = 0;
    base64Decoder(hashBase64, storedHash, hashSize);

    // 3: Hash the entered password with the same salt and parameters
    unsigned char newHash[32];
    int result = argon2d_hash_raw(timeCost, memoryCost, parallelism,
                                  enteredPassword.c_str(), enteredPassword.size(),
                                  salt, saltSize, newHash, hashSize);

    if (result != ARGON2_OK) {
        throw std::runtime_error("Error: Hashing failed during verification");
    }

    // 4: Compare the hashes
    return std::memcmp(storedHash, newHash, hashSize) == 0;
}

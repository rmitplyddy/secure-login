#ifndef DATABASE_UTILS
#define DATABASE_UTILS

#include "DatabaseConnection.h"
#include "PasswordHasher.h"
#include "auth/AuthModel.h"
#include "user/UserModel.h"

#include <string>

namespace Database {

    std::string validateUser(const std::shared_ptr<Model::Authenticator> auth);
    std::string createUser(std::unique_ptr<Model::User> newUser);

}

#endif // DATABASE_UTILS
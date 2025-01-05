#include "AuthModel.h"

namespace Model {
    AuthenticatorModel::AuthenticatorModel(std::string uname, std::string pw) 
                    : username(uname), password(pw) {

    }
}

// bool Authenticator::authenticate(void) {

//     Database::validateUser(username, password);
// }


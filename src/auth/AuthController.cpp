#include "AuthController.h"

void AuthenticatorControl::initConnections(void) {
    connect(this->authView, &AuthenticatorView::processAuthentication, 
                this, &AuthenticatorControl::handleUserAuthentication);
    connect(this->authView, &AuthenticatorView::displayNewUserScreen, 
                this, &AuthenticatorControl::switchToNewUserView);
}

void AuthenticatorControl::handleUserAuthentication(void) {
    auto userDTO = std::make_unique<UserDTO>(authView->getUsername(),
                    authView->getPassword());

    std::string authResult = authModel->authenticateUser(userDTO);

    if (authResult != "SUCCESS") {
        this->authView->displayViewError(authResult);
    }
    else {
        emit loginSuccess();
    }
}

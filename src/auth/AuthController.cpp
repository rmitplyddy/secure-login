#include "AuthController.h"

void AuthenticatorControl::initConnections(void) {
    connect(this->authView, &AuthenticatorView::processAuthentication, 
                this, &AuthenticatorControl::handleUserAuthentication);
    connect(this->authView, &AuthenticatorView::displayNewUserScreen, 
                this, &AuthenticatorControl::switchToNewUserView);
}

void AuthenticatorControl::handleUserAuthentication(void) {
    qDebug() << "Control: Ready to handle user Authentication";

    auto userDTO = std::make_unique<UserDTO>(authView->getUsername(),
                    authView->getPassword());

    if (!authModel->authenticateUser(std::move(userDTO))) {
        std::string errMsg = "Incorrect username or password";
        this->authView->displayViewError(errMsg);
    }
    else {
        emit loginSuccess();
    }
}

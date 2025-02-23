#include "AuthController.h"


// IView AuthenticatorControl::getView() {
//     return *authView;
// }

void AuthenticatorControl::initConnections(void) {
    connect(this->authView, &AuthenticatorView::processAuthentication, 
                this, &AuthenticatorControl::handleUserAuthentication);
    connect(this->authView, &AuthenticatorView::displayNewUserScreen, 
                this, &AuthenticatorControl::switchToNewUserView);
}

void AuthenticatorControl::handleUserAuthentication(void) {
    qDebug() << "Control: Ready to handle user Authentication";
    // emit loginSuccess();
    if (authModel->authenticateUser(authView->getUsername(), 
                    authView->getPassword())) {
        emit loginSuccess();
    // // handle user authentication here
    }
    else {
        std::string errMsg = "Incorrect username or password";
        this->authView->displayViewError(errMsg);
    }
}

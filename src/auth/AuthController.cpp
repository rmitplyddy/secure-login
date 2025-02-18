#include "AuthController.h"


// IView AuthenticatorControl::getView() {
//     return *authView;
// }

void AuthenticatorControl::initConnections(void) {
    connect(this->authView, &AuthenticatorView::onButtonClicked, 
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
        std::cout << "yet to authenticate" << std::endl;
    }
}


// void AuthenticatorControl::handleNewUserRequest(void) {
//     qDebug() <<"Control: Ready to pass to new user request screen";
//     // applicationControl->createNewUser(); // takes to new user screen
// }
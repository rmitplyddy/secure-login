#include "AuthController.h"

void AuthenticatorControl::handleUserAuthentication(void) {
    qDebug() << "Control: Ready to handle user Authentication";

}


void AuthenticatorControl::handleNewUserRequest(void) {
    qDebug() <<"Control: Ready to pass to new user request screen";
    // applicationControl->createNewUser(); // takes to new user screen
}
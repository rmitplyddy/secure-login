#include "NewUserController.h"

void NewUserController::initConnections(void) {
    connect(this->newUserView, &NewUserView::signUpUser, this, 
            &NewUserController::handleNewUser);
    connect(this->newUserView, &NewUserView::displayLoginScreen, this, 
            &NewUserController::switchToLoginScreen);
}

void NewUserController::handleNewUser(void) {

    std::cout << newUserView->getUsername() << std::endl;

    auto userDTO = std::make_unique<UserDTO>(newUserView->getUsername(),
                    newUserView->getPassword());

    if (model->createUser(userDTO)) {
        emit signalNewUserSuccess();
    }
}

#include "NewUserController.h"

void NewUserController::initConnections(void) {
    connect(this->newUserView, &NewUserView::signUpUser, this, &NewUserController::handleNewUser);
    connect(this->newUserView, &NewUserView::displayLoginScreen, this, &NewUserController::switchToLoginScreen);
}

void NewUserController::handleNewUser(void) {

    std::cout << newUserView->getUsername() << std::endl;

    // check password match ??

    model->createUser(newUserView->getUsername(), newUserView->getPassword());

    qDebug() << "Control: ready to handle new user";
    
    emit signalNewUserSuccess();

}

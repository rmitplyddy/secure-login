#include "AppController.h"

void ApplicationControl::authenticateUser(void) {

    if (!authView) { // if view not initialised (lazy initialisation)
        authView = std::make_unique<AuthenticatorView>();
        authControl = std::make_unique<AuthenticatorControl>(model, authView.get());
        connect(authControl.get(), &AuthenticatorControl::loginSuccess, this, &ApplicationControl::initialiseApplication);
        connect(authControl.get(), &AuthenticatorControl::switchToNewUserView, this, &ApplicationControl::createNewUser);
        // connect button press
    }

    authView->show();

    if (newUserView) {
        newUserView->resetView();
        newUserView->hide();
    }
}

void ApplicationControl::createNewUser(void) {

    std::cout << "new user button pressed" << std::endl;

    if (!newUserView) {
        newUserView = std::make_unique<NewUserView>();
        newUserControl = std::make_unique<NewUserController>(newUserView.get(), model);
        connect(newUserControl.get(), &NewUserController::switchToLoginScreen, this, &ApplicationControl::authenticateUser);
        connect(newUserControl.get(), &NewUserController::signalNewUserSuccess, this, &ApplicationControl::handleNewUserSuccess);
        // connect button press
    }

    newUserView->show();

    if (authView) {
        authView->resetView();
        authView->hide();
    }
}

void ApplicationControl::handleNewUserSuccess(void) {

    std::string message = "New User: ";
    message.append(newUserView->getUsername());
    message.append(" added! Continue to login ");

    QString qMessage = QString::fromStdString(message);

    QMessageBox::information(nullptr, "Welcome! ", qMessage, QMessageBox::Ok);
    
    authenticateUser();
}

void ApplicationControl::initialiseApplication(void) {
    std::cout << "application intialisation commence" << std::endl;

}



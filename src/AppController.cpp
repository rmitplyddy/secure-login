#include "AppController.h"

void ApplicationControl::authenticateUser(void) {

    if (!authView) { // if view not initialised (lazy initialisation)
        authView = std::make_unique<AuthenticatorView>();
        authControl = std::make_unique<AuthenticatorControl>(model,
                                                            authView.get());
        connect(authControl.get(), &AuthenticatorControl::loginSuccess, 
                                this, &ApplicationControl::initialiseApplication);
        connect(authControl.get(), 
                &AuthenticatorControl::switchToNewUserView, 
                    this, &ApplicationControl::createNewUser);
    }

    authView->show();

    if (newUserView) {
        newUserView->resetView();
        newUserView->hide();
    }
}

void ApplicationControl::createNewUser(void) {

    if (!newUserView) {
        newUserView = std::make_unique<NewUserView>();
        newUserControl = std::make_unique<NewUserController>(
                                                        newUserView.get(), model);
        connect(newUserControl.get(), &NewUserController::switchToLoginScreen, 
                                        this, &ApplicationControl::authenticateUser);
        connect(newUserControl.get(), &NewUserController::signalNewUserSuccess, 
                                    this, &ApplicationControl::handleNewUserSuccess);
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

    std::string message = "Login Success!\n Welcome " ;
    message.append(authView->getUsername());
    QString qMessage = QString::fromStdString(message);
    QMessageBox::information(nullptr, "Welcome! ", qMessage, QMessageBox::Ok);
    
    if (authView) {
        authView->resetView();
        authView->hide();
    }

    // set to close program. remove if further building required
    QApplication::quit();
}



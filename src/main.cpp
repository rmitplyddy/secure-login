#include <stdlib.h>
#include <iostream>
#include <QApplication>

#include "AppController.h"
#include "auth/AuthController.h"
#include "auth/AuthModel.h"
#include "auth/AuthView.h"


void createNewUser(void) {

}


int main(int argc, char* argv[]) {

    // std::string dbDirectory = "";

    QApplication app(argc, argv);
    // QWidget window;

    // plug in authenticator control after database

    ApplicationControl appControl;
    appControl.authenticateUser();
    // auto authControl = AuthenticatorControl();


    // auto authView = std::make_unique<AuthenticatorView>(authControl);
    

    // authView->show();
    // may need to load main controller into subcontrollersß
    // std::cout << "FIXME" << std::endl;

    return app.exec();         // Start event loop
}
#include <stdlib.h>
#include <iostream>
#include <QApplication>

// #include "AppController.h"
#include "auth/AuthController.h"
#include "auth/AuthModel.h"
#include "auth/AuthView.h"



int main(int argc, char* argv[]) {

    // std::string dbDirectory = "";

    QApplication app(argc, argv);
    // QWidget window;

    // plug in authenticator control after database

    // auto authControl = std::make_unique<AuthenticatorControl>();
    // auto authView = std::make_unique<AuthenticatorView>();

    auto authModel = std::make_shared<AuthenticatorModel>();
    auto authControl = std::make_shared<AuthenticatorControl>(authModel);
    auto authView = std::make_unique<AuthenticatorView>(authControl);

    authView->show();

    std::cout << "FIXME" << std::endl;

    return app.exec();         // Start event loop
}
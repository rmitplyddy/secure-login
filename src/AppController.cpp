#include "AppController.h"
#include <iostream>

ApplicationControl::ApplicationControl(/*std::string dbPath*/) {
    std::cout << "here" << std::endl;
    // initDatabase(dbPath);
    authenticateUser();
}


// void initDatabase(std::string dbPath) {
//     // trigger database initialisation
//     // model to handle any necessary functionality
//     auto db = std::make_unique<Database::DatabaseAdmin>(dbPath);
//     if (!db->checkDatabaseExists()) {
//         db->initUserTable();
//     }
// }


void ApplicationControl::authenticateUser(void) {

    // auto authView = std::make_unique<AuthenticatorView>();

    std::cout << "here" << std::endl;
    auto authModel = std::make_unique<AuthenticatorModel>();
    auto authControl = std::make_unique<AuthenticatorControl>(std::move(authModel));
    auto authView = std::make_unique<AuthenticatorView>(std::move(authControl));

    authView->show();

}





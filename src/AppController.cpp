#include "AppController.h"


// ApplicationControl::ApplicationControl(/*std::string dbPath*/) {
//     std::cout << "here" << std::endl;
//     // initDatabase(dbPath);
//     // authenticateUser();
// }


// void initDatabase(std::string dbPath) {
//     // trigger database initialisation
//     // model to handle any necessary functionality
//     auto db = std::make_unique<Database::DatabaseAdmin>(dbPath);
//     if (!db->checkDatabaseExists()) {
//         db->initUserTable();
//     }
// }


void ApplicationControl::authenticateUser(void) {

    auto authModel = std::make_shared<Model::AuthenticatorModel>();
    auto authControl = AuthenticatorControl(this, authModel);
    authView = std::make_unique<AuthenticatorView>(authControl);
    authView->show();
}

void ApplicationControl::createNewUser(void) {

    // auto newUserModel = std::make_shared<Model::NewUserModel>();
    // auto newUserControl = std::make_shared<NewUserController>(this, newUserModel);
    // auto newUserView = std::make_unique<NewUserView>(newUserControl);
    // newUserView->show();

}





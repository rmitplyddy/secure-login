#include "AppController.h"


ApplicationControl::ApplicationControl(std::string dbPath) {
    initDatabase(dbPath);
}


void initDatabase(std::string dbPath) {
    // trigger database initialisation
    // model to handle any necessary functionality
    auto db = std::make_unique<Database::DatabaseAdmin>(dbPath);
    if (!db->checkDatabaseExists()) {
        db->initUserTable();
    }
}






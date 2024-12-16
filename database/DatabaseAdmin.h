#ifndef DB_ADMIN
#define DB_ADMIN

#include <iostream>
#include <fstream>
#include <memory>

#include "DatabaseConnection.h"
#include "DatabaseAdmin.h"

namespace Database {
    class DatabaseAdmin {
    public:
        DatabaseAdmin(std::string path);
        bool checkDatabaseExists(void);
        void initUserTable(void);
        void deleteUserTable(void);

    private:
        std::string dbPath;
    };
}


#endif //DB_ADMIN
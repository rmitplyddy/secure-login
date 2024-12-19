#ifndef APP_CONTROLLER
#define APP_CONTROLLER


// #include "database/DatabaseAdmin.h"
#include "auth/AuthController.h"
#include "auth/AuthModel.h"
#include "auth/AuthView.h"

class ApplicationControl {

public:
    ApplicationControl(/* std::string dbPath */);
    void authenticateUser(void);

private:
    // std::shared_ptr<AuthenticatorControl> authControl;
    // std::shared_ptr<AuthenticatorView> authView;
    // std::shared_ptr<AuthenticatorModel> authModel;

};


#endif // APP_CONTROLLER
#ifndef AUTH_CONTROL
#define AUTH_CONTROL


#include "AuthModel.h"
// #include "AuthView.h"


class AuthenticatorControl {


public:
    AuthenticatorControl() {}
    AuthenticatorControl(std::shared_ptr<AuthenticatorModel> model) 
                                        : authModel(model) {}

protected:


private:
    std::shared_ptr<AuthenticatorModel> authModel;

};

#endif //AUTH_CONTROL
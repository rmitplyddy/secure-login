#ifndef AUTH_CONTROL
#define AUTH_CONTROL

#include "AuthModel.h"
#include "AuthView.h"


class AuthenticatorControl {


protected:
    AuthenticatorControl();

private:
    AuthenticatorModel model;

};

#endif //AUTH_CONTROL
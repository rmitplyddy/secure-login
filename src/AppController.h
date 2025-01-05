#ifndef APP_CONTROLLER
#define APP_CONTROLLER

#include <iostream>
#include <QObject>

// #include "database/DatabaseAdmin.h"
#include "auth/AuthController.h"
#include "auth/AuthModel.h"
#include "auth/AuthView.h"
#include "user/new/NewUserController.h"
#include "user/new/NewUserModel.h"
#include "user/new/NewUserView.h"



class ApplicationControl : public QObject {

Q_OBJECT

public:
    ApplicationControl(QObject *parent = nullptr /* std::string dbPath */) : 
                        QObject(parent) {
        authView = nullptr;
        qDebug() << "app control called";
    }

public slots:
    void authenticateUser(void);
    void createNewUser(void);

private:
    // application window

    // std::shared_ptr<AuthenticatorControl> authControl;
    std::unique_ptr<AuthenticatorView> authView;
    // std::shared_ptr<AuthenticatorModel> authModel;

};


#endif // APP_CONTROLLER
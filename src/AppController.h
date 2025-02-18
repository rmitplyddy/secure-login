#ifndef APP_CONTROLLER
#define APP_CONTROLLER

#include <iostream>
#include <QObject>
#include <QMessageBox>

// #include "database/DatabaseAdmin.h"
#include "auth/AuthController.h"
#include "auth/AuthModel.h"
#include "auth/AuthView.h"
#include "user/new/NewUserController.h"
#include "user/new/NewUserModel.h"
#include "user/new/NewUserView.h"
#include "ModelFacade.h"



class ApplicationControl : public QObject {

Q_OBJECT

public:
    ApplicationControl(QObject *parent = nullptr /* std::string dbPath */) : 
                        QObject(parent) {
        model = std::make_shared<Model::ModelFacade>();
        // authView = nullptr;
        qDebug() << "app control called";
    }

public slots:
    void authenticateUser(void);
    void createNewUser(void);
    void initialiseApplication(void);
    void handleNewUserSuccess(void);

private:
    // application window

    std::unique_ptr<AuthenticatorControl> authControl;
    std::unique_ptr<AuthenticatorView> authView;

    std::shared_ptr<Model::ModelFacade> model;

    std::unique_ptr<NewUserController> newUserControl;
    std::unique_ptr<NewUserView> newUserView;

};


#endif // APP_CONTROLLER
#ifndef AUTH_CONTROL
#define AUTH_CONTROL


#include "AuthModel.h"
#include "src/AppController.h"

#include <QDebug>
#include <QObject>

#include <memory>
// #include "AuthView.h"

class ApplicationControl;

class AuthenticatorControl : public QObject {

Q_OBJECT

public:
    AuthenticatorControl(QObject *parent = nullptr) : 
                                    QObject(parent) {}
    // AuthenticatorControl(std::shared_ptr<Model::AuthenticatorModel> model) : 
    //                     authModel(model) {
    //     // applicationControl = std::make_unique<ApplicationControl>(appControl);
    // }

    AuthenticatorControl(ApplicationControl& appControl, 
                        std::shared_ptr<Model::AuthenticatorModel> model,
                        QObject *parent = nullptr ) : QObject(parent),
                        authModel(model) {
        applicationControl = std::make_unique<ApplicationControl>(appControl);
    }

public slots:
    void handleUserAuthentication(void);
    void handleNewUserRequest(void);

protected:


private:
    std::weak_ptr<Model::AuthenticatorModel> authModel;
    std::unique_ptr<ApplicationControl> applicationControl;

};

#endif //AUTH_CONTROL
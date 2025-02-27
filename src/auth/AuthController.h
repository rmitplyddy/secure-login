#ifndef AUTH_CONTROL
#define AUTH_CONTROL

#include "src/auth/AuthModel.h"
#include "src/ModelFacade.h"
#include "AuthView.h"

#include <QDebug>
#include <QObject>
#include <memory>

class AuthenticatorControl : public QObject {

Q_OBJECT

public:
    AuthenticatorControl(QObject *parent = nullptr) : 
                         QObject(parent) {
        initConnections();
        authView->show();
    }

    AuthenticatorControl(AuthenticatorView* view, QObject *parent = nullptr) : 
                        QObject(parent), authView(view) {
        initConnections();
        authView->show();
    }

    AuthenticatorControl(std::shared_ptr<Model::ModelFacade> model, 
                        AuthenticatorView* view, QObject *parent = nullptr) : 
                        QObject(parent), authView(view) {
        initConnections();
        authView->show();
    }

    void initConnections(void);

signals:
    void switchToNewUserView(void);
    void loginSuccess(void);

public slots:
    void handleUserAuthentication(void);



private:
    AuthenticatorView* authView;
    std::shared_ptr<Model::ModelFacade> authModel;
};

#endif //AUTH_CONTROL
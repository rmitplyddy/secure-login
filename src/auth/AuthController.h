#ifndef AUTH_CONTROL
#define AUTH_CONTROL


#include "src/auth/AuthModel.h"
#include "src/ModelFacade.h"
#include "AuthView.h"

// #include "src/AppController.h"

#include <QDebug>
#include <QObject>
#include <memory>

// class ApplicationControl;

class AuthenticatorControl : public QObject {

Q_OBJECT

public:
    AuthenticatorControl(QObject *parent = nullptr) : 
                         QObject(parent) {
        // authView = std::make_unique<AuthenticatorView>();
        initConnections();
        authView->show();
        qDebug() << "Authview should be reached";
    }

    AuthenticatorControl(AuthenticatorView* view, QObject *parent = nullptr) : 
                        QObject(parent), authView(view) {
        initConnections();
        authView->show();
        qDebug() << "Authview should be reached";
    }

    AuthenticatorControl(std::shared_ptr<Model::ModelFacade> model, 
                        AuthenticatorView* view, QObject *parent = nullptr) : 
                        QObject(parent), authView(view) {
        // authModel = model;
        initConnections();
        authView->show();
        qDebug() << "Model loaded";
    }

    void initConnections(void);

    // IView getView();
    // AuthenticatorControl(std::shared_ptr<Model::AuthenticatorModel> model) : 
    //                     authModel(model) {
    //     // applicationControl = std::make_unique<ApplicationControl>(appControl);
    // }

    // AuthenticatorControl(ApplicationControl& appControl, 
    //                     std::shared_ptr<Model::AuthenticatorModel> model,
    //                     QObject *parent = nullptr ) : QObject(parent),
    //                     authModel(model) {
    //     applicationControl = std::make_unique<ApplicationControl>(appControl);
    // }
signals:
    void switchToNewUserView(void);
    void loginSuccess(void);

public slots:
    void handleUserAuthentication(void);



private:
    AuthenticatorView* authView;
    // std::unique_ptr<AuthenticatorView> authView;
    std::shared_ptr<Model::ModelFacade> authModel;
    // std::unique_ptr<ApplicationControl> applicationControl;

};

#endif //AUTH_CONTROL
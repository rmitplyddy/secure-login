#ifndef NEW_USER_CONTROL
#define NEW_USER_CONTROL

#include "src/ModelFacade.h"
#include "NewUserView.h"

#include <iostream>
#include <QDebug>

class NewUserController : public QObject {

Q_OBJECT

public:
    NewUserController(NewUserView* view, 
                        std::shared_ptr<Model::ModelFacade> mf, 
                        QObject* parent = nullptr) : 
                        QObject(parent), model(mf),
                        newUserView(view)
                        {
        initConnections();
    }
    void initConnections(void);
    void handleNewUser(void);

signals:
    void switchToLoginScreen(void);
    void signalNewUserSuccess(void);

private:
    std::shared_ptr<Model::ModelFacade> model;
    NewUserView* newUserView;

};


#endif // NEW_USER_CONTROL
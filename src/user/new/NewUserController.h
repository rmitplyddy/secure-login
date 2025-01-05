#ifndef NEW_USER_CONTROL
#define NEW_USER_CONTROL

#include "NewUserModel.h"
#include "src/AppController.h"

#include <QDebug>

class NewUserController {

public: 
    NewUserController(std::shared_ptr<Model::NewUserModel> model) : 
                        newUserModel(model) {
        // applicationControl = std::make_unique<ApplicationControl>(appControl);
    }

    // NewUserController(ApplicationControl& appControl, 
    //                     std::shared_ptr<Model::NewUserModel> model) : 
    //                     newUserModel(model) {
    //     applicationControl = std::make_unique<ApplicationControl>(appControl);
    // }
    void handleNewUser(void);
    void handleCurrentUser(void);

private:
    std::shared_ptr<Model::NewUserModel> newUserModel;
    // std::shared_ptr<ApplicationControl> applicationControl;

};


#endif // NEW_USER_CONTROL
# secure-login.pro

#QMAKE_MAC_SDK = macosx15.0

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14


# Specify Qt modules used in the project
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = secure-login

TEMPLATE = app

SOURCES += src/main.cpp \
            src/CustomTextInput.cpp \
            src/AppController.cpp \
            src/ModelFacade.cpp \
            src/auth/AuthController.cpp \
            src/user/UserBaseView.cpp \
            src/auth/AuthView.cpp \
            src/user/new/NewUserController.cpp \
            src/user/new/NewUserView.cpp \
             src/database/PasswordHasher.cpp \
            src/database/DatabaseUtils.cpp \
            src/database/DatabaseAdmin.cpp 
           

HEADERS += src/AppController.h \
            src/ModelFacade.h \
            src/UserDTO.h \
            src/CustomTextInput.h \
            src/auth/AuthController.h \
            src/user/UserBaseView.h \
            src/auth/AuthView.h \
            src/user/new/NewUserController.h \
            src/user/new/NewUserView.h \
            src/database/PasswordHasher.h \
            src/database/DatabaseUtils.h \
            src/database/DatabaseAdmin.cpp 
            

INCLUDEPATH += /opt/homebrew/opt/qt/include \
                /opt/homebrew/opt/sqlite/include \
                /opt/homebrew/opt/argon2/include

LIBS += -F/opt/homebrew/Cellar/qt/6.7.3/lib -framework QtCore -framework QtGui \
        -L/opt/homebrew/opt/sqlite/lib -lsqlite3 \
        -L/opt/homebrew/opt/argon2/lib -largon2
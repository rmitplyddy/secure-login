# secure-login.pro

#QMAKE_MAC_SDK = macosx15.0

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14


# Specify Qt modules used in the project
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Define the name of the target executable
TARGET = secure-login

# Define the type of template (application)
TEMPLATE = app

# Add the source files
SOURCES += src/main.cpp src/auth/AuthView.cpp src/auth/AuthController.cpp src/auth/AuthModel.cpp

# Add header files (if any)
HEADERS += src/AppController.h src/auth/AuthView.h # Add your .h files here

# Optionally, add include paths for external libraries (if needed)
INCLUDEPATH += /opt/homebrew/opt/qt/include

# Optionally, link Qt libraries explicitly
#LIBS += -F/opt/homebrew/opt/qt/lib -framework Qt6Core -framework Qt6Gui


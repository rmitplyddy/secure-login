#include <QApplication>

#include "AppController.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    ApplicationControl appControl;
    appControl.authenticateUser();

    return app.exec();
}
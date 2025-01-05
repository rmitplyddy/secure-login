#ifndef NEWUSER_VIEW
#define NEWUSER_VIEW

#include <QApplication>
#include <QTextStream>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDebug>

#include "NewUserController.h"

class NewUserView : public QWidget {

public:
    NewUserView();
    NewUserView(std::shared_ptr<NewUserController> control);
    void showView();
    std::string setUsername(void);
    std::string setPassword(void);

private:
    std::shared_ptr<NewUserController> controller;
    QPushButton* signupButton;
    QLabel* currentUserLabel;
    QLineEdit* usernameInput;
    QLineEdit* passwordInput;

private slots:

    void onButtonClick(void);
    void onHyperlinkClicked(const QString& link);

};


#endif // NEWUSER_VIEW
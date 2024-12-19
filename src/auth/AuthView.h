#ifndef AUTH_VIEW
#define AUTH_VIEW

#include <QApplication>
#include <QTextStream>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>

#include <iostream>

#include "AuthController.h"

class AuthenticatorView : public QWidget {

Q_OBJECT

public:
    AuthenticatorView(QWidget* parent = nullptr) : QWidget(parent) {
        setView();
    }
    // AuthenticatorView(QWidget* parent = nullptr, 
    //                         std::unique_ptr<AuthenticatorControl> authControl);
    AuthenticatorView(std::shared_ptr<AuthenticatorControl> authControl);
    // parent QWidget to handle deletion of raw ptrs
    std::string getUsername(void);
    std::string getPassword(void);

protected:
    void setView(void);


private:
    std::unique_ptr<AuthenticatorControl> authController;
    QPushButton* loginButton;
    QLabel* newUserLabel;
    QLineEdit* usernameInput;
    QLineEdit* passwordInput;
    

private slots:
    // slots used to support signals / listeners
    void onButtonClicked(void);
    void onHyperlinkClicked(const QString& link);

// signals:
//     void pressedLoginButton(void);

};

#endif // AUTH_VIEW
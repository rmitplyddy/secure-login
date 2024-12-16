#ifndef AUTH_VIEW
#define AUTH_VIEW

#include <QApplication>
#include <QTextStream>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class AuthenticatorView {

public:
    AuthenticatorView();
    std::string getUsername(void);
    std::string getPassword(void);
    QPushButton getButton(void);

protected:
    void setView(void);


private:
    QPushButton LoginButton;
    std::unique_ptr<QLabel> newUserLabel;
    std::unique_ptr<QLineEdit> usernameInput;
    std::unique_ptr<QLineEdit> passwordInput;

};

#endif // AUTH_VIEW
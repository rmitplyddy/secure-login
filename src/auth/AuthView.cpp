#ifndef AUTH_VIEW
#define AUTH_VIEW

#include <QApplication>
#include <QTextStream>
#include <QPushButton>
#include <QLabel>

class AuthenticatorView {

public:
    std::string getUsername(void);
    std::string getPassword(void);
    QPushButton getButton(void);

private:
    QPushButton LoginButton;
    QLabel NewUserLabel;

};

#endif // AUTH_VIEW
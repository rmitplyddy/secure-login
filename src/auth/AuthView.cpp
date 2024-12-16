#include "AuthView.h"

AuthenticatorView::AuthenticatorView() {
    setView()
}

void AuthenticatorView::setView(void) {

}

std::string AuthenticatorView::getUsername(void) {
    QString usernameStr = usernameInput->text();
    return usernameStr.toStdString();
}

std::string AuthenticatorView::getPassword(void) {
    QString pwString = passwordInput->text();
    return pwString.toStdString();
}

QPushButton AuthenticatorView::getButton(void) {


}
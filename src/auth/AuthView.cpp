#include "AuthView.h"


// AuthenticatorView::AuthenticatorView(QWidget* parent, 
//                                     std::unique_ptr<AuthenticatorControl> authControl) : 
//                                 QWidget(parent), authController(std::move(authControl)) {
//     setView();
// }

AuthenticatorView::AuthenticatorView(std::shared_ptr<AuthenticatorControl> authControl) {
    QWidget(nullptr); // produce own window
    setView();
}



void AuthenticatorView::setView(void) {

    newUserLabel = new QLabel(this);
    usernameInput = new QLineEdit(this);
    passwordInput = new QLineEdit(this);
    loginButton = new QPushButton(this);

    auto vBox = new QVBoxLayout(this);

    // new user option to take user to window

    newUserLabel->setText("Not yet a user? Click <a href='#'>here...</a>");
    newUserLabel->setOpenExternalLinks(false);
    connect(newUserLabel, &QLabel::linkActivated, this, 
                        &AuthenticatorView::onHyperlinkClicked);

    // textbox configuration
    usernameInput->setPlaceholderText("Username:");
    usernameInput->setMaxLength(50);
    passwordInput->setPlaceholderText("Password:");
    passwordInput->setMaxLength(50);

    // set button
    loginButton->setText("Login");
    connect(loginButton, &QPushButton::clicked, this, 
                                &AuthenticatorView::onButtonClicked);


    
    vBox->addWidget(usernameInput);
    vBox->addWidget(passwordInput);
    vBox->addWidget(loginButton);
    vBox->addWidget(newUserLabel);
    setLayout(vBox);
}


void AuthenticatorView::onButtonClicked() {
    qDebug() << "Login Button pressed"; // output to console
}



void AuthenticatorView::onHyperlinkClicked(const QString& link) {
    // FIXME
    qDebug () << "Hyperlink clicked";

}

std::string AuthenticatorView::getUsername(void) {
    QString usernameStr = usernameInput->text();
    return usernameStr.toStdString();
}

std::string AuthenticatorView::getPassword(void) {
    QString pwString = passwordInput->text();
    return pwString.toStdString();
}

#include "AuthView.h"


AuthenticatorView::AuthenticatorView(QWidget* parent) : UserBaseView(parent) {
    setView();

}


void AuthenticatorView::setView(void) {

    vBox = new QVBoxLayout();
    newUserLabel = new QLabel(this);
    // new user option to take user to window

    newUserLabel->setText("Not yet a user? Click <a href='#'>here...</a>");
    newUserLabel->setOpenExternalLinks(false);
    connect(newUserLabel, &QLabel::linkActivated, this, 
                        &AuthenticatorView::onHyperlinkClicked);

    // textbox configuration
    getUsernameInput()->getTextBox()->setPlaceholderText("Username");
    getUsernameInput()->getTextBox()->setMaxLength(50);
    getPasswordInput()->getTextBox()->setPlaceholderText("Password");
    getPasswordInput()->getTextBox()->setMaxLength(50);

    // set button
    getButton()->setText("Login");

    vBox->addWidget(getViewErrorLabel());
    vBox->addWidget(getUsernameInput());
    vBox->addWidget(getPasswordInput());
    vBox->addWidget(getButton());
    vBox->addWidget(newUserLabel);
    setLayout(vBox);
}


void AuthenticatorView::onButtonClicked() {
    qDebug() << "Login Button pressed"; // output to console
    emit pressedButton();

    if (!checkInputBoxes(vBox)){
        emit processAuthentication();
    }
}

void AuthenticatorView::onHyperlinkClicked(void) {
    // FIXME
    qDebug () << "Hyperlink clicked";
    emit displayNewUserScreen();
}

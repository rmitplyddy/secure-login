#include "NewUserView.h"

NewUserView::NewUserView() {
    QWidget(nullptr);
    showView();
}

NewUserView::NewUserView(std::shared_ptr<NewUserController> control) {
    QWidget(nullptr);
    showView();
}

void NewUserView::showView() {
    signupButton = new QPushButton();
    currentUserLabel = new QLabel();
    usernameInput = new QLineEdit();
    passwordInput = new QLineEdit();

    currentUserLabel->setText("Not yet a user? Click <a href='#'>here...</a>");
    currentUserLabel->setOpenExternalLinks(false);
    connect(currentUserLabel, &QLabel::linkActivated, this, 
                        &NewUserView::onHyperlinkClicked);

    connect(signupButton, &QPushButton::clicked, this, 
                            &NewUserView::onButtonClick);



    // textbox configuration
    usernameInput->setPlaceholderText("Username:");
    usernameInput->setMaxLength(50);
    passwordInput->setPlaceholderText("Password:");
    passwordInput->setMaxLength(50);

    auto vBox = new QVBoxLayout(this);

    setLayout(vBox);


}

void NewUserView::onButtonClick() {
    qDebug() << "New user Button clicked!";
    controller->handleNewUser();

}


void NewUserView::onHyperlinkClicked(const QString& link) {
    qDebug() << "Return to sign in screen";
    controller->handleCurrentUser();

}


std::string NewUserView::setUsername(void) {

}

std::string NewUserView::setPassword(void) {


}
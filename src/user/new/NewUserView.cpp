#include "NewUserView.h"

const int NewUserView::MIN_PW_LENGTH = 12;
const int NewUserView::MIN_USERNAME_LENGTH = 12;

NewUserView::NewUserView(QWidget* parent) : UserBaseView(parent) {
    vBox = new QVBoxLayout(this);
    setView();
}

void NewUserView::setView() {

    confirmPasswordInput = new CustomTextInput("Confirm Password", 
                                                    PASSWORD, this);
    currentUserLabel = new QLabel();
    currentUserLabel->setText("Already a user? Click <a href='#'>here...</a>");
    currentUserLabel->setOpenExternalLinks(false);
    connect(currentUserLabel, &QLabel::linkActivated, this, 
                        &NewUserView::onHyperlinkClicked);

    getButton()->setText("Sign up");

    vBox->addWidget(getUsernameInput());
    vBox->addWidget(getPasswordInput());
    vBox->addWidget(confirmPasswordInput);
    vBox->addWidget(getButton());
    vBox->addWidget(currentUserLabel);

    setLayout(vBox);
}

bool NewUserView::checkPasswordsMatch(void) {
    
    bool mismatch = true;

    if (getPasswordInput()->getUserInput() != 
                                        confirmPasswordInput->getUserInput()) {
        getPasswordInput()->displayError();
        confirmPasswordInput->displayError("Passwords must match!");
        // 
    }
    else {
        getPasswordInput()->clearError();
        confirmPasswordInput->clearError();
        mismatch = false;
    }
    return mismatch;
}


bool NewUserView::validatePasswordInput(void) {

    // check password length meets minimum length

    bool match = checkPasswordsMatch();
    bool invalid = true;

    int count = getPasswordInput()->getUserInput().length();
    if (count < MIN_PW_LENGTH) {
        std::string minCharError = "Password must be greater than ";
        minCharError.append(std::to_string(MIN_PW_LENGTH));
        minCharError.append(" characters!");
        getPasswordInput()->displayError(minCharError);
        // 
    }
    else {
        getPasswordInput()->clearError();
        invalid = false;
    }

    qDebug() << std::to_string(invalid || match);

    return invalid || match;
}




void NewUserView::onButtonClicked(void) {
    qDebug() << "New user Button clicked!";

    bool valid = false;

    if (checkInputBoxes(vBox)) {
        // do nothing
        qDebug() << "empty input box!";
    } else if (validatePasswordInput()) {
        connect(getPasswordInput()->getTextBox(), &QLineEdit::textChanged, 
                this, &NewUserView::validatePasswordInput);
    }  else {
        emit signUpUser();
    }
}


void NewUserView::onHyperlinkClicked(void) {
    qDebug() << "Return to sign in screen";
    emit displayLoginScreen();
}


std::string NewUserView::getUsername(void) {
    return getUsernameInput()->getUserInput();
}

std::string NewUserView::getPassword(void) {
    return getPasswordInput()->getUserInput();
}
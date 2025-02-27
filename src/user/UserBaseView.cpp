#include "UserBaseView.h"

UserBaseView::UserBaseView(QWidget* parent) : QWidget(parent) {

    button = new QPushButton();
    connect(button, &QPushButton::clicked, this, 
                                &UserBaseView::onButtonClicked);

    usernameInput = new CustomTextInput("Username", REGULAR);
    passwordInput = new CustomTextInput("Password", PASSWORD);

    viewError = new QLabel();
    viewError->setVisible(false);
    viewError->setStyleSheet("color: red");
}


void UserBaseView::resetView(void) {

    clearViewError();

    // clears all character inputs from user
    for (auto* widget : findChildren<QLineEdit*>()) {
        widget->clear();
    }

    // reset all errors on custom input block
    for (auto* input : findChildren<CustomTextInput*>()) {
        input->clearError();
    }
}


void UserBaseView::displayViewError(std::string& errorMsg) {

    // member to display error passed from model layers

    QString error = QString::fromStdString(errorMsg);
    viewError->setText(error);
    viewError->setVisible(true);
} 

void UserBaseView::clearViewError(void) {

    // remove the error displayed in the view

    viewError->clear();
    viewError->setVisible(false);
}


bool UserBaseView::checkInputBoxes(QLayout* layout) {

    // recursive function to find nested custom layouts
    // with empty text boxes

    qDebug() << "Checking widgets...";
    qDebug() << layout->count();

    bool isEmpty = false;

    for (int i = 0; i < layout->count(); ++i) {
        QLayoutItem* item = layout->itemAt(i);
        if (QWidget* widget = item->widget()) {
            qDebug() << "Widget type: " << widget->metaObject()->className();
            if (CustomTextInput* inputBox = 
                qobject_cast<CustomTextInput*>(widget)) {
                if (inputBox->getUserInput().empty()) {
                    isEmpty = true;
                    inputBox->displayError("Box cannot be empty... ");
                    connect(inputBox->getTextBox(), &QLineEdit::textChanged, 
                            inputBox, &CustomTextInput::clearError);
                }
            }
        } 
        else if (QLayout* nestedLayout = item->layout()) {
            isEmpty = checkInputBoxes(nestedLayout);
        }
    }
    return isEmpty;
}
#include "UserBaseView.h"


UserBaseView::UserBaseView(QWidget* parent) : QWidget(parent) {

    button = new QPushButton();
    connect(button, &QPushButton::clicked, this, 
                                &UserBaseView::onButtonClicked);

    usernameInput = new CustomTextInput("Username");
    passwordInput = new CustomTextInput("Password" );
}


void UserBaseView::resetView(void) {

    for (auto* widget : findChildren<QLineEdit*>()) {
        widget->clear();
    }


    for (auto* input : findChildren<CustomTextInput*>()) {
        input->clearError();
    }

}


bool UserBaseView::checkInputBoxes(QLayout* layout) {

    // utility function

    // recursive function to find nested custom layouts
    // and empty text boxes

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
                    connect(inputBox->getTextBox(), &QLineEdit::textChanged, inputBox, 
                        &CustomTextInput::clearError);
                }
            }
        } 
        else if (QLayout* nestedLayout = item->layout()) {
            isEmpty = checkInputBoxes(nestedLayout);
        }
    }
    return isEmpty;
}
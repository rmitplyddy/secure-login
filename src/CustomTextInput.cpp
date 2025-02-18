#include "CustomTextInput.h"

const QString CustomTextInput::REG_TEXT_BOX_STYLE = "";
const QString CustomTextInput::ERROR_TEXT_BOX_STYLE = "border: 2px solid red;";
const QString CustomTextInput::ERROR_LABEL_STYLE = "colour: red";

std::string CustomTextInput::getUserInput(void) const {
    return textBox->text().toStdString();
}

QLayout* CustomTextInput::getLayout(void) {
    return vBox;
}

bool CustomTextInput::operator!=(const CustomTextInput* other) const {
    return textBox->text().toStdString() != other->getUserInput();
}

void CustomTextInput::displayError(std::string errMsg) {

    QString errorText = QString::fromStdString(errMsg);
    textBox->setStyleSheet(ERROR_TEXT_BOX_STYLE);
    errorLabel->setText(errorText);
    errorLabel->setStyleSheet(ERROR_LABEL_STYLE);
    errorLabel->setVisible(true);

}

void CustomTextInput::clearError(void) {

    textBox->setStyleSheet(REG_TEXT_BOX_STYLE);
    errorLabel->clear();
    errorLabel->setVisible(false);
    disconnect(textBox, &QLineEdit::textChanged, this, 
                    &CustomTextInput::clearError);

}
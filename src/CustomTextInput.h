#ifndef CUSTOM_TEXT_INPUT
#define CUSTOM_TEXT_INPUT

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

#include <string>

enum TextBoxType {

    REGULAR,
    PASSWORD

};

class CustomTextInput : public QWidget {

    Q_OBJECT

    public:
        explicit CustomTextInput(const QString labelTxt, 
                                TextBoxType boxtype = REGULAR,
                                QWidget* parent = nullptr) :
                                QWidget(parent), type(boxtype) {
            textBox = new QLineEdit();
            textBox->setPlaceholderText(labelTxt);

            if (type == PASSWORD) {
                textBox->setEchoMode(QLineEdit::Password);
                textBox->setContextMenuPolicy(Qt::NoContextMenu);
            }
            inputLabel = new QLabel();
            inputLabel->setText(labelTxt + ":");
            errorLabel = new QLabel();
            errorLabel->setVisible(false);

            vBox = new QVBoxLayout();
            vBox->addWidget(inputLabel);
            vBox->addWidget(textBox);
            vBox->addWidget(errorLabel);
            setLayout(vBox);
            connect(textBox, &QLineEdit::textChanged, this, 
                    &CustomTextInput::clearError);
        };
        QLineEdit* getTextBox(void) { return textBox; }
        QLayout* getLayout(void);
        std::string getUserInput(void) const;
        void displayError(std::string errMsg = "");
        bool operator!=(const CustomTextInput* other) const;

    public slots:
        void clearError(void);

    private:
        TextBoxType type;
        QVBoxLayout* vBox;
        QLineEdit* textBox;
        QLabel* errorLabel;
        QLabel* inputLabel;
        static const QString REG_TEXT_BOX_STYLE;
        static const QString ERROR_TEXT_BOX_STYLE;
        static const QString ERROR_LABEL_STYLE;


};


#endif // CUSTOM_TEXT_INPUT
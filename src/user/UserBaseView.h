#ifndef USER_BASE_VIEW
#define USER_BASE_VIEW

#include "src/CustomTextInput.h"

#include <QApplication>
#include <QTextStream>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>




class UserBaseView : public QWidget {

Q_OBJECT

public:
    UserBaseView(QWidget* parent = nullptr);
    virtual void setView(void) = 0;
    std::string getUsername(void) { 
        return usernameInput->getUserInput();
    }
    std::string getPassword(void) {
        return passwordInput->getUserInput();
    }
    void resetView(void);
    bool checkInputBoxes(QLayout* layout);

protected:
    CustomTextInput* getUsernameInput(void) { return usernameInput; }
    CustomTextInput* getPasswordInput(void) { return passwordInput; }
    QPushButton* getButton(void) { return button; }

private:
    QPushButton* button;
    CustomTextInput* usernameInput;
    CustomTextInput* passwordInput;

signals:
    void pressedButton(void);
    void displayScreen(void);

public slots:
    // slots used to support signals / listeners
    virtual void onButtonClicked(void) = 0;

};


#endif //USER_BASE_VIEW

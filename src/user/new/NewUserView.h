#ifndef NEWUSER_VIEW
#define NEWUSER_VIEW

#include "src/user/UserBaseView.h"


class NewUserView : public UserBaseView {

Q_OBJECT

public:
    NewUserView(QWidget* parent = nullptr);
    void setView(void) override;
    std::string getUsername(void);
    std::string getPassword(void);
    bool checkPasswordsMatch(void);

private:
    QPushButton* signupButton;
    QLabel* currentUserLabel;
    QVBoxLayout* vBox;

    CustomTextInput* usernameInput;
    CustomTextInput* passwordInput;
    CustomTextInput* confirmPasswordInput;

    const static int MIN_PW_LENGTH;
    const static int MIN_USERNAME_LENGTH;


signals:
    void signUpUser(void);
    void displayLoginScreen(void);

public slots:
    bool validatePasswordInput(void);
    void onButtonClicked(void) override;
    void onHyperlinkClicked(void);

};


#endif // NEWUSER_VIEW
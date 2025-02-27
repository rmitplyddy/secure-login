#ifndef AUTH_VIEW
#define AUTH_VIEW

#include "src/user/UserBaseView.h"
#include "src/IView.h"


class AuthenticatorView : public UserBaseView {

Q_OBJECT

public:
    AuthenticatorView(QWidget* parent = nullptr);

private:
    void setView(void) override;
    QLabel* newUserLabel; // hyperlink
    QVBoxLayout* vBox;

signals:
    void displayNewUserScreen(void);
    void processAuthentication(void);

public slots:
    // slots used to support signals / listeners
    void onButtonClicked(void) override;
    void onHyperlinkClicked(void);

};

#endif // AUTH_VIEW
#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QDialog>
#include "User.h"

class QLineEdit;
class QVBoxLayout;
class QFormLayout;
class QWidget;

class LoginWindow: public QDialog
{
    Q_OBJECT

public:
    LoginWindow();
    User loggedInUser;

private slots:
    void auth();
    void enableLoginButton();

private:
    void createWidgets();
    void addHeaderLayout();
    void addFormLayout();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
};

#endif

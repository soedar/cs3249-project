#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QMainWindow>

class QLineEdit;
class QVBoxLayout;
class QWidget;

class LoginWindow: public QMainWindow
{
public:
    LoginWindow();

private:
    void createWidgets();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;
};

#endif
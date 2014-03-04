#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QMainWindow>

class QLineEdit;
class QVBoxLayout;
class QFormLayout;
class QWidget;

class LoginWindow: public QMainWindow
{
public:
    LoginWindow();

private:
    void createWidgets();
    void addHeaderLayout();
    void addFormLayout();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;
};

#endif
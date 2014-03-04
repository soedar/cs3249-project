#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QDialog>

class QLineEdit;
class QVBoxLayout;
class QFormLayout;
class QWidget;

class LoginWindow: public QDialog
{
    Q_OBJECT

public:
    LoginWindow();

private slots:
    void auth();

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
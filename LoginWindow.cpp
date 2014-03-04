#include <QtGui>
#include "LoginWindow.h"
#include "UserDb.h"
#include "User.h"

LoginWindow::LoginWindow()
{
    setGeometry(0, 0, 550, 300);
    createWidgets();
    setWindowTitle(tr("The Anatomy Academy: Login"));
}

void LoginWindow::createWidgets()
{
    mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

    addHeaderLayout();
    addFormLayout();

    setLayout(mainLayout);
}

void LoginWindow::addHeaderLayout()
{
    QVBoxLayout *headerLayout = new QVBoxLayout;
    headerLayout->setSpacing(2);
    headerLayout->setContentsMargins(0, 0, 0, 40);

    QLabel *name = new QLabel(tr("The Anatomy Academy"));
    name->setFont(QFont(NULL, 32));
    name->setAlignment(Qt::AlignCenter);
    name->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QLabel *tagLine = new QLabel(tr("Some tag line"));
    tagLine->setAlignment(Qt::AlignCenter);
    tagLine->setFont(QFont(NULL, 15));
    tagLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    headerLayout->addWidget(name);
    headerLayout->addWidget(tagLine);

    mainLayout->addLayout(headerLayout);
}

void LoginWindow::addFormLayout()
{
    QFormLayout *formLayout = new QFormLayout;
    formLayout->setFormAlignment(Qt::AlignHCenter);

    QLabel *emailLabel = new QLabel(tr("Email:"));
    emailLineEdit = new QLineEdit;
    emailLineEdit->setFixedWidth(220);
    formLayout->addRow(emailLabel, emailLineEdit);

    QLabel *passwordLabel = new QLabel(tr("Password:"));
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setFixedWidth(220);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    formLayout->addRow(passwordLabel, passwordLineEdit);

    loginButton = new QPushButton(tr("Login"));
    loginButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    loginButton->setEnabled(false);
    formLayout->addWidget(loginButton);

    connect(emailLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableLoginButton()));
    connect(passwordLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableLoginButton()));
    connect(loginButton, SIGNAL(clicked()), this, SLOT(auth()));

    mainLayout->addLayout(formLayout);
}

// slots

void LoginWindow::auth()
{
    QString inputEmail = emailLineEdit->text();
    QString inputPassword = passwordLineEdit->text();

    User user = UserDb::userWithEmail(emailLineEdit->text());
    if (user.email() != inputEmail) {
        QMessageBox::critical(this, tr("Login Failed"), tr("Email address not found"));
    } else if (user.password() != inputPassword) {
        QMessageBox::critical(this, tr("Login Failed"), tr("Invalid password"));
    } else {
        this->loggedInUser = user;
        this->done(1);
    }
}

void LoginWindow::enableLoginButton()
{
    if (emailLineEdit->text() != "" && passwordLineEdit->text() != "") {
        loginButton->setEnabled(true);
    } else { 
        loginButton->setEnabled(false);
    }
}
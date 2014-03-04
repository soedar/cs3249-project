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

    QPushButton *loginButton = new QPushButton(tr("Login"));
    loginButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    formLayout->addWidget(loginButton);

    connect(loginButton, SIGNAL(clicked()), this, SLOT(auth()));

    mainLayout->addLayout(formLayout);
}

void LoginWindow::auth()
{
    QString inputEmail = emailLineEdit->text();
    QString inputPassword = passwordLineEdit->text();

    User user = UserDb::userWithEmail(emailLineEdit->text());
    if (user.email() != inputEmail) {
        qDebug() << "No such user";
    } else if (user.password() != inputPassword) {
        qDebug() << "Wrong password";
    } else {
        this->done(1);
    }
    //this->done(1);
}
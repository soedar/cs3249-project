#include <QtGui>
#include "LoginWindow.h"

LoginWindow::LoginWindow()
{
    setGeometry(0, 0, 650, 450);

    createWidgets();
}

void LoginWindow::createWidgets()
{
    centralWidget = new QWidget;

    mainLayout = new QVBoxLayout;
    centralWidget->setLayout(mainLayout);

    QHBoxLayout *emailLayout = new QHBoxLayout;
    QLabel *emailLabel = new QLabel(tr("&E-mail:"));
    emailLineEdit = new QLineEdit;
    emailLabel->setBuddy(emailLineEdit);
    emailLayout->addWidget(emailLabel);
    emailLayout->addWidget(emailLineEdit);

    QHBoxLayout *passwordLayout = new QHBoxLayout;
    QLabel *passwordLabel = new QLabel(tr("&Password:"));
    passwordLineEdit = new QLineEdit;
    passwordLabel->setBuddy(passwordLineEdit);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordLineEdit);

    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(emailLayout);
    mainLayout->addLayout(passwordLayout);

    setCentralWidget(centralWidget);
}
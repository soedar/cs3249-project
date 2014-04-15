#include "MainWidget.h"

MainWidget::MainWidget()
{
    setGeometry(0, 0, 650, 500);
	lessons = LessonsDBController::getDB();
}

void MainWidget::createWidgets()
{
    mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

    createButtons();
    initializeTable();
    populateTableData();

    setLayout(mainLayout);
}

void MainWidget::createButtons()
{
    QHBoxLayout *topHeader = new QHBoxLayout;
    topHeader->setAlignment(Qt::AlignRight);

    profileButton = new QPushButton(QIcon(":/assets/profile.png"), tr("My Profile"),this);
    profileButton->setEnabled(true);
    topHeader->addWidget(profileButton);

    logOutButton = new QPushButton(QIcon(":/assets/log_out.png"), tr("Log Out"), this);
    logOutButton->setEnabled(true);
    topHeader->addWidget(logOutButton);

    mainLayout->addLayout(topHeader);
}

void MainWidget::initializeTable()
{}

void MainWidget::populateTableData()
{}

void MainWidget::updateTable()
{
    mainTable->clear();
    populateTableData();
}

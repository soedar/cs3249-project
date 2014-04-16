#include "MenuWidget.h"
#include <QDebug>

#define MENU_BUTTON_WIDTH   50
#define MENU_BUTTON_HEIGHT  150

MenuWidget::MenuWidget(QWidget *parent, Lesson *lesson) : QWidget(parent)
{
    setGeometry(0,0,400,parentWidget()->size().height());
    mainLayout = new QHBoxLayout;
    this->lesson = lesson;


    menuContentWidget = new QWidget(this);
    menuContentWidget->setStyleSheet("background-color:gray;");

    setupMenuWidgets();

    //menuLayout->addWidget(menu);
    mainLayout->addWidget(menuContentWidget);

    menuButton = new QPushButton(tr(">"));
    menuButton->setMaximumWidth(MENU_BUTTON_WIDTH);
    menuButton->setMinimumHeight(MENU_BUTTON_HEIGHT);
    mainLayout->addWidget(menuButton);

    setLayout(mainLayout);

    connect(menuButton, SIGNAL(clicked()), this, SLOT(toggle()));

    isOpened = true;
    toggle();

    qDebug() << LessonsDBController::getDB()->getTopics();
}

void MenuWidget::setupMenuWidgets()
{
    QVBoxLayout *menuLayout = new QVBoxLayout;
    menuContentWidget->setLayout(menuLayout);

    // Self Test
    QPushButton *testButton = new QPushButton(tr("\t\t\t\t\tTake the \n \t\t\t\t\tself test"));
    connect(testButton, SIGNAL(clicked()), this, SLOT(testPressed()));

    QPixmap pixmap(":/assets/test.png");
    QIcon buttonIcon(pixmap);
    testButton->setIcon(buttonIcon);
    testButton->setIconSize(pixmap.rect().size());

    testButton->setStyleSheet("background-color: none; font-size: 18pt; height: 80px");
    menuLayout->addWidget(testButton);


    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QPixmap lessonPixmap(":/assets/lessons32.png");
    QIcon lessonButtonIcon(lessonPixmap);
    lessonButton = new QToolButton();
    lessonButton->setStyleSheet("background-color: none; font-size: 14pt; height: 60px; width: 60px");
    lessonButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    lessonButton->setIcon(lessonButtonIcon);
    lessonButton->setIconSize(lessonPixmap.rect().size());
    lessonButton->setText("Lesson");

    QPixmap profilePixmap(":/assets/profile32.png");
    QIcon profileButtonIcon(profilePixmap);
    profileButton = new QToolButton();
    profileButton->setStyleSheet("background-color: none; font-size: 14pt; height: 60px; width: 60px");
    profileButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    profileButton->setIcon(profileButtonIcon);
    profileButton->setIconSize(profilePixmap.rect().size());
    profileButton->setText("Profile");

    QPixmap logoutPixmap(":/assets/log_out32.png");
    QIcon logoutButtonIcon(logoutPixmap);
    logoutButton = new QToolButton();
    logoutButton->setStyleSheet("background-color: none; font-size: 14pt; height: 60px; width: 60px");
    logoutButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    logoutButton->setIcon(logoutButtonIcon);
    logoutButton->setIconSize(logoutPixmap.rect().size());
    logoutButton->setText("Logout");


    buttonLayout->addWidget(lessonButton);
    buttonLayout->addWidget(profileButton);
    buttonLayout->addWidget(logoutButton);

    menuLayout->addLayout(buttonLayout);

}

void MenuWidget::toggle()
{
    if (isOpened) {
        setGeometry(0, 0, 55, parentWidget()->size().height());
        menuContentWidget->setHidden(true);
        menuButton->setText(tr(">"));
    } else {
        setGeometry(0, 0, 400, parentWidget()->size().height());
        menuContentWidget->setHidden(false);
        menuButton->setText(tr("<"));
    }

    isOpened = !isOpened;
}

void MenuWidget::adjustSize()
{
    setGeometry(0, 0, size().width(), parentWidget()->size().height()); 
}

void MenuWidget::testPressed()
{
    emit selectTest(false);
}

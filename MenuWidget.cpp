#include "MenuWidget.h"
#include <QDebug>

#define MENU_BUTTON_WIDTH   50
#define MENU_BUTTON_HEIGHT  150

MenuWidget::MenuWidget(QWidget *parent, DatabaseLayer *db) : QWidget(parent)
{
    this->db = db;
    setGeometry(0,0,400,parentWidget()->size().height());
    mainLayout = new QHBoxLayout;

    menu = new QLabel(tr("This is my menu"));

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

    isOpened = false;
    toggle();

    qDebug() << LessonsDBController::getDB().getTopics();
}

void MenuWidget::setupMenuWidgets()
{
    QVBoxLayout *menuLayout = new QVBoxLayout;
    menuContentWidget->setLayout(menuLayout);

    QPushButton *testButton = new QPushButton(tr("\t\t\t\t\tTake the \n \t\t\t\t\tself test"));

    QPixmap pixmap(":/assets/test.png");
    QIcon buttonIcon(pixmap);
    testButton->setIcon(buttonIcon);
    testButton->setIconSize(pixmap.rect().size());

    testButton->setStyleSheet("background-color: none; font-size: 18pt; height: 80px");
    menuLayout->addWidget(testButton);
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
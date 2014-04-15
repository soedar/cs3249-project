#include "MenuWidget.h"
#include <QDebug>

#define MENU_BUTTON_WIDTH   50
#define MENU_BUTTON_HEIGHT  150

MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent)
{
    setGeometry(0,0,400,parentWidget()->size().height());
    mainLayout = new QHBoxLayout;

    menu = new QLabel(tr("This is my menu"));

    menuContentWidget = new QWidget(this);
    menuContentWidget->setStyleSheet("background-color:gray;");
    QVBoxLayout *menuLayout = new QVBoxLayout;
    menuContentWidget->setLayout(menuLayout);
    //menuLayout->addWidget(menu);

    mainLayout->addWidget(menuContentWidget);

    QPushButton *button = new QPushButton(tr(">"));

    button->setMaximumWidth(MENU_BUTTON_WIDTH);
    button->setMinimumHeight(MENU_BUTTON_HEIGHT);
    mainLayout->addWidget(button);

    setLayout(mainLayout);

    connect(button, SIGNAL(clicked()), this, SLOT(toggle()));

    isOpened = false;
    toggle();
}

void MenuWidget::toggle()
{
    if (isOpened) {
        setGeometry(0, 0, 55, parentWidget()->size().height());
        menuContentWidget->setHidden(true);
    } else {
        setGeometry(0, 0, 400, parentWidget()->size().height());
        menuContentWidget->setHidden(false);
    }

    isOpened = !isOpened;
}

void MenuWidget::adjustSize()
{
    setGeometry(0, 0, size().width(), parentWidget()->size().height()); 
}
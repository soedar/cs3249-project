#include "MenuWidget.h"

#define MENU_BUTTON_WIDTH   50
#define MENU_BUTTON_HEIGHT  100

MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout;
    setGeometry(0,0,500,parent->size().height());


    menuLayout = new QVBoxLayout;
    mainLayout->addLayout(menuLayout);

    menu = new QLabel(tr("This is my menu"));
    menuLayout->addWidget(menu);


    QPushButton *button = new QPushButton(tr(">"));
    button->setMaximumWidth(MENU_BUTTON_WIDTH);
    button->setMinimumHeight(MENU_BUTTON_HEIGHT);
    button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    mainLayout->addWidget(button);

    setLayout(mainLayout);

    connect(button, SIGNAL(clicked()), this, SLOT(toggle()));

    isOpened = false;
    toggle();
}

void MenuWidget::toggle()
{
    if (isOpened) {
        menu->setHidden(true);
        setGeometry(0,0,MENU_BUTTON_WIDTH,parentWidget()->size().height());
    } else {
        menu->setHidden(false);
        setGeometry(0,0,500,parentWidget()->size().height());
    }

    isOpened = !isOpened;
}
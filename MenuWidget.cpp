#include "MenuWidget.h"

MenuWidget::MenuWidget()
{
    mainLayout = new QVBoxLayout;
    QLabel *menu = new QLabel(tr("This is my menu"));

    mainLayout->addWidget(menu);
    setStyleSheet("background-color:blue;");
    setLayout(mainLayout);
    QPushButton *button = new QPushButton(tr("Adjust"));
    mainLayout->addWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(adjust()));
}

void MenuWidget::adjust()
{
    /*
    qDebug("here");
    setGeometry(0,0,500,500);
    */
}
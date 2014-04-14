#include "MenuWidget.h"

MenuWidget::MenuWidget()
{
    mainLayout = new QHBoxLayout;
    QLabel *menu = new QLabel(tr("This is my menu"));

    mainLayout->addWidget(menu);

    setStyleSheet("background-color:blue;");
    setLayout(mainLayout);
    QPushButton *button = new QPushButton(tr(">"));
    mainLayout->addWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(adjust()));
}

void MenuWidget::adjust()
{
    raise();
    resize(400, height());
}
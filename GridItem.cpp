#include "GridItem.h"

GridItem::GridItem()
{
}

void GridItem::initLabel(const QString &string)
{
    mainLayout = new QHBoxLayout();
    name = string;
    label = new QPushButton(QIcon(":/assets/diagrams.png"), tr(name.toStdString().c_str()));
    label->setEnabled(false);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);
    cross = new QPushButton(QIcon(":/assets/cross.png"),tr(""));
    cross->setEnabled(false);
    cross->setVisible(false);
    mainLayout->setAlignment(Qt::AlignRight | Qt::AlignTop);
    mainLayout->addWidget(cross);
    setLayout(mainLayout);

}

QPushButton GridItem::getButton()
{
    return cross;
}

void GridItem::enterEvent(QEvent *event)
{
    cross->setVisible(true);
    cross->setEnabled(true);
}

void GridItem::leaveEvent(QEvent *event)
{
    cross->setEnabled(false);
    cross->setVisible(false);
}

void GridItem::exit()
{
    this->destroy(true,true);
}

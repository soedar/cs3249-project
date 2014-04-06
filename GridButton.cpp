#include "GridButton.h"

GridButton::GridButton(QWidget *parent) : QPushButton(parent)
{
    index = 0;
}

void GridButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        emit rightClicked();
    }
    else
    {
        emit leftClicked();
        return;
    }
}

void GridButton::setIndex(int ind)
{
    index = ind;
}

int GridButton::getIndex()
{
    return index;
}

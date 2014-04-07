#include "GridButton.h"

GridButton::GridButton(QWidget *parent) : QToolButton(parent)
{
    index = 0;
    setFixedSize(80,60);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
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

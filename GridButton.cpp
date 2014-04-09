#include "GridButton.h"


//This is the button that will be inside the file uploader and image uploader
GridButton::GridButton(QWidget *parent) : QToolButton(parent)
{
    index = 0;

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
    }
}

void GridButton::enterEvent(QEvent *event)
{
    emit entered();
}
void GridButton::leaveEvent(QEvent *event)
{
    emit left();
}

void GridButton::setIndex(int ind)
{
    index = ind;
}

int GridButton::getIndex()
{
    return index;
}

#include "CustomLine.h"

CustomLine::CustomLine()
{
    pos1 = QPoint(0,0);
    pos2 = QPoint(1,1);
    setLine(0,0,1,1);
}

QRectF CustomLine::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void CustomLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QGraphicsLineItem::paint(painter,option,widget);
    painter->drawLine(pos1,pos2);
}

void CustomLine::setPos1(QPointF posChange)
{
    pos1.setX(posChange.x()+5);
    pos1.setY(posChange.y()+5);
    setLine(pos1.x()+5,pos1.y()+5,pos2.x()+5,pos2.y()+5);
    update();
}
void CustomLine::setPos2(QPointF posChange)
{
    pos2.setX(posChange.x()+5);
    pos2.setY(posChange.y()+5);
    setLine(pos1.x()+5,pos1.y()+5,pos2.x()+5,pos2.y()+5);
    update();
}

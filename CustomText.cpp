#include "CustomText.h"

CustomText::CustomText()
{
    setFlag(QGraphicsTextItem::ItemIsMovable);
    //setFlag(QGraphicsItem::ItemIsMovable);
    setTextInteractionFlags(Qt::TextEditorInteraction);
    setPlainText("Type here");
    setTextWidth(50);
    selected = false;
}

QRectF CustomText::boundingRect() const
{
    return QRectF(0,0,80,60);
}

void CustomText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsTextItem::paint(painter,option,widget);
    painter->drawRect(boundingRect());
}

void CustomText::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    selected = true;
    QGraphicsItem::mousePressEvent(event);
}

void CustomText::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (selected)
    {
       QPointF temp;
       temp.setX(this->pos().x());
       temp.setY(this->pos().y());
       emit moved(temp);
       temp.setX(this->pos().x()+10);
       temp.setY(this->pos().y()+60);
       emit movedForLine(temp);
    }

    QGraphicsItem::mouseMoveEvent(event);
}

void CustomText::recieveChange(QPointF posChange)
{
    posChange.setX(posChange.x()-10);
    posChange.setY(posChange.y()-60);
    this->setPos(posChange);
}

void CustomText::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    selected = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

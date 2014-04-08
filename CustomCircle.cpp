#include "CustomCircle.h"

CustomCircle::CustomCircle()
{
    selected = false;
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);

}


QRectF CustomCircle::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void CustomCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->fillRect(boundingRect(),QBrush(Qt::red));
   painter->drawRect(boundingRect());

}



void CustomCircle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    selected = true;
    qDebug("I am clicked\n");
    //update();
    QGraphicsItem::mousePressEvent(event);
}

void CustomCircle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (selected)
    {
       emit moved(this->pos());
    }
    //update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CustomCircle::recieveChange(QPointF posChange)
{
    posChange.setX(posChange.x()+10);
    posChange.setY(posChange.y()+60);
    this->setPos(posChange);
}

void CustomCircle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    selected = false;
    //update();
    QGraphicsItem::mouseReleaseEvent(event);
}

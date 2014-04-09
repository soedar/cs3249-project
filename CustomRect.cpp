#include "CustomRect.h"

CustomRect::CustomRect()
{
    selected = false;
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable,false);

}


QRectF CustomRect::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void CustomRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->fillRect(boundingRect(),QBrush(Qt::red));
   painter->drawRect(boundingRect());

}

void CustomRect::setIndex(int i)
{
    index = i;
}


void CustomRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    selected = true;
    qDebug("I am clicked\n");
    //update();
    QGraphicsItem::mousePressEvent(event);
}

void CustomRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (selected)
    {
       emit moved(this->pos());
    }
    //update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CustomRect::recieveChange(QPointF posChange)
{
    posChange.setX(posChange.x()+10);
    posChange.setY(posChange.y()+60);
    this->setPos(posChange);
}

void CustomRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    selected = false;
    //update();
    QGraphicsItem::mouseReleaseEvent(event);
}

int CustomRect::getIndex()
{
    return index;
}

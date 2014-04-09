#ifndef CUSTOMLINE_H
#define CUSTOMLINE_H

#include "CustomRect.h"

class CustomLine : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    CustomLine();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setIndex(int i);
    int index;
    int getIndex();

private:
    QPointF pos1;
    QPointF pos2;

public slots:
    void setPos1(QPointF posChange);
    void setPos2(QPointF posChange);

};

#endif // CUSTOMLINE_H

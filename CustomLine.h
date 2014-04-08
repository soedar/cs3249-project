#ifndef CUSTOMLINE_H
#define CUSTOMLINE_H

#include "CustomCircle.h"

class CustomLine : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    CustomLine();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPointF pos1;
    QPointF pos2;

public slots:
    void setPos1(QPointF posChange);
    void setPos2(QPointF posChange);

};

#endif // CUSTOMLINE_H

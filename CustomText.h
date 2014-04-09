#ifndef CUSTOMTEXT_H
#define CUSTOMTEXT_H

#include "CustomLine.h"

class CustomText : public QGraphicsTextItem
{
    Q_OBJECT
public:
    CustomText();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setIndex(int i);
    int index;
    int getIndex();

private:
    bool selected;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void recieveChange(QPointF posChange);

signals:
    void moved(QPointF posChange);
    void movedForLine(QPointF posChange);
};

#endif // CUSTOMTEXT_H

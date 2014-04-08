#ifndef CUSTOMCIRCLE_H
#define CUSTOMCIRCLE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "qdebug.h"

class CustomCircle : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    CustomCircle();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    bool selected;

protected:
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void recieveChange(QPointF posChange);

signals:
    void moved(QPointF posChange);
};

#endif // CUSTOMCIRCLE_H

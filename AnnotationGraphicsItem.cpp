#include "AnnotationGraphicsItem.h"

AnnotationGraphicsItem::AnnotationGraphicsItem()
{
    box = new CustomText();
    boxRect = new CustomRect();
    lineRect = new CustomRect();
    line = new CustomLine();

    connect(box,SIGNAL(moved(QPointF)),boxRect,SLOT(recieveChange(QPointF)));
    connect(box,SIGNAL(movedForLine(QPointF)),line,SLOT(setPos1(QPointF)));
    connect(boxRect,SIGNAL(moved(QPointF)),box,SLOT(recieveChange(QPointF)));
    connect(lineRect,SIGNAL(moved(QPointF)),line,SLOT(setPos2(QPointF)));
    connect(boxRect,SIGNAL(moved(QPointF)),line,SLOT(setPos1(QPointF)));

    box->setPos(10,50);
    boxRect->setPos(10,110);
    lineRect->setPos(10,150);
    line->setPos1(QPoint(10,110));
    line->setPos2(QPoint(10,150));
}

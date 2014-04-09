#include "AnnotationGraphicsItem.h"


//Box is a text box u can edit for the annotation
//box Rect and line Rect are 2 pointers u can drag and use as 'anchors'
//line is just the line that connects the rect pointers.
//Note this is just a grouping class. You cannot physically put this object itself into a scene.
AnnotationGraphicsItem::AnnotationGraphicsItem()
{
    box = new CustomText();
    boxRect = new CustomRect();
    lineRect = new CustomRect();
    line = new CustomLine();

    //signals that, when u move one of the items, update the positions of the other items.
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

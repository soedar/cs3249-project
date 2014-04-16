#include "CustomImage.h"

CustomImage::CustomImage()
{
    annotations = QList<AnnotationGraphicsItem *>();
}

void CustomImage::setAnnos(QList<AnnotationGraphicsItem *> list)
{
    annotations.clear();
    for (int i=0; i<list.size(); i++)
    {
        annotations.push_back(list.at(i));
    }
}

void CustomImage::addAnno(AnnotationGraphicsItem *item)
{
    annotations.push_back(item);
}

void CustomImage::removeAnno(int ind)
{
    AnnotationGraphicsItem *item =  annotations.takeAt(ind);
    delete item;
}

void CustomImage::setPos(int ind, QPointF pos1, QPointF pos2, const QString &string)
{
    AnnotationGraphicsItem *item = annotations.at(ind);

    item->box->setPos(QPointF(pos1.x(),pos1.y()-60));
    item->box->setPlainText(string);
    item->boxRect->setPos(pos1);
    item->lineRect->setPos(pos2);
    item->line->setPos1(pos1);
    item->line->setPos2(pos2);
}

void CustomImage::updateIndices()
{
    for (int i=0; i<annotations.size(); i++)
    {
        AnnotationGraphicsItem *tempItem = annotations.at(i);
        tempItem->box->setIndex(i);
        tempItem->boxRect->setIndex(i);
        tempItem->line->setIndex(i);
        tempItem->lineRect->setIndex(i);
    }
}

void CustomImage::setIndex(int ind)
{
    index = ind;
}

int CustomImage::getIndex()
{
    return index;
}

QList<AnnotationGraphicsItem *> CustomImage::getAnnos()
{
    return annotations;
}

void CustomImage::clear()
{
    int numAnnos = annotations.size();
    for (int i=0; i<numAnnos; i++)
    {
        AnnotationGraphicsItem *tempItem = annotations.takeLast();
    }
    annotations.clear();
}

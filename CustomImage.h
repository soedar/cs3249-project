#ifndef CUSTOMIMAGE_H
#define CUSTOMIMAGE_H
#include "AnnotationGraphicsItem.h"

class CustomImage
{
public:
    CustomImage();
    void setAnnos(QList<AnnotationGraphicsItem *> list);
    void setIndex(int ind);

    int getIndex();
    QList<AnnotationGraphicsItem *> getAnnos();

    void addAnno(AnnotationGraphicsItem *item);
    void removeAnno(int ind);
    void updateIndices();
private:
    QList<AnnotationGraphicsItem *> annotations;
    int index;
};

#endif // CUSTOMIMAGE_H

#ifndef ANNOTATIONGRAPHICSITEM_H
#define ANNOTATIONGRAPHICSITEM_H

#include "CustomText.h"

class AnnotationGraphicsItem : public QObject
{
    Q_OBJECT
public:
    AnnotationGraphicsItem();
    CustomText *box;
    CustomRect *boxRect;
    CustomRect *lineRect;
    CustomLine *line;
};

#endif // ANNOTATIONGRAPHICSITEM_H

#include "CustomScene.h"


//Added extra signal here with the mousepressevent

CustomScene::CustomScene(QObject *parent) :
    QGraphicsScene(parent)
{
    deleting = false;
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (deleting)
    {
        emit clicked();
    }
    QGraphicsScene::mousePressEvent(event);
}

void CustomScene::setDelete(bool del)
{
    deleting = del;
}

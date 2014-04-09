#include "CustomScene.h"

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

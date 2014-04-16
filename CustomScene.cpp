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

void CustomScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A)
    {
        emit toTheLeft();
    }
    else if (event->key() == Qt::Key_D)
    {
        emit toTheRight();
    }
    QGraphicsScene::keyPressEvent(event);
}

void CustomScene::setDelete(bool del)
{
    deleting = del;
}

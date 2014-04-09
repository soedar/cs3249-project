#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QObject *parent = 0);
    void setDelete(bool del);

private:
    bool deleting;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked();

public slots:

};

#endif // CUSTOMSCENE_H

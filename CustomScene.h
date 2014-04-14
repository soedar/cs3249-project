#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>

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
    void keyPressEvent(QKeyEvent *event);

signals:
    void clicked();
    void toTheLeft();
    void toTheRight();

public slots:

};

#endif // CUSTOMSCENE_H

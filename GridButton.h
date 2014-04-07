#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

#include <QToolButton>
#include <QMouseEvent>
#include <QEvent>

class GridButton : public QToolButton
{
    Q_OBJECT
public:
    explicit GridButton(QWidget *parent = 0);
    void setIndex(int ind);
    int getIndex();

signals:
    void rightClicked();
    void leftClicked();

public slots:
    void mousePressEvent(QMouseEvent *event);

private:
    int index;
};

#endif // QGRIDBUTTON_H

#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QMouseEvent>
#include <QEvent>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>


class GridItem : public QWidget
{
    Q_OBJECT
public:
    GridItem();
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    void setLabel(const QString &string);
    void initLabel(const QString &string);
    QPushButton getButton();
private:
    QPushButton *label;
    QPushButton *cross;
    QHBoxLayout *mainLayout;
    QString name;

public slots:
    void exit();
};

#endif // GRIDITEM_H

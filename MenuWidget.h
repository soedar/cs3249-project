#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    MenuWidget(QWidget *parent);


private:
    QHBoxLayout *mainLayout;

    QVBoxLayout *menuLayout;
    bool isOpened;
    QLabel *menu;

private slots:
    void toggle();

};

#endif
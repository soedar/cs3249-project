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
    void adjustSize();

private:
    QHBoxLayout *mainLayout;

    QWidget *menuContentWidget;

    bool isOpened;
    QLabel *menu;

private slots:
    void toggle();

};

#endif
#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "DatabaseLayer.h"

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    MenuWidget(QWidget *parent, DatabaseLayer *db);
    void adjustSize();

private:
    DatabaseLayer *db;
    QHBoxLayout *mainLayout;

    QWidget *menuContentWidget;

    bool isOpened;
    QLabel *menu;
    QPushButton *menuButton;

    void setupMenuWidgets();

private slots:
    void toggle();

};

#endif
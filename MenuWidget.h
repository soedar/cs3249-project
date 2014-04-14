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
    MenuWidget();


private:
    QVBoxLayout *mainLayout;


private slots:
    void adjust();
};

#endif
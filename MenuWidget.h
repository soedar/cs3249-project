#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include "DatabaseLayer.h"
#include "Lesson.h"

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    MenuWidget(QWidget *parent, Lesson *lesson);
    void adjustSize();

    QToolButton *logoutButton;
    QToolButton *profileButton;
    QToolButton *lessonButton;

private:
    DatabaseLayer *db;
    QHBoxLayout *mainLayout;

    QWidget *menuContentWidget;

    bool isOpened;
    QPushButton *menuButton;
    Lesson *lesson;

    void setupMenuWidgets();

signals:
    void selectTest(bool);
    
private slots:
    void toggle();
    void testPressed();

};

#endif

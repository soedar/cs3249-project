#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "LessonsDBController.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLineEdit>
#include <QFormLayout>
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();
    virtual void populateTableData();

    QPushButton *logOutButton;
     QPushButton *profileButton;

protected:
    void createWidgets();
    void createButtons();
    virtual void initializeTable();

    LessonsDB lessons;
    QVBoxLayout *mainLayout;



    QTableWidget *mainTable;

public slots:
    void updateTable();
};

#endif

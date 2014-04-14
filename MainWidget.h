#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "LessonsDBController.h"
#include "TestsDB.h"

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
    Q_OBJECT;

public:
    MainWidget();
    virtual void populateTableData();

    QPushButton *logOutButton;

protected:
    void createWidgets();
    void createButtons();
    virtual void initializeTable();

    LessonsDB lessons;
    QVBoxLayout *mainLayout;
    QPushButton *profileButton;

    QTableWidget *mainTable;

public slots:
    void updateTable();
};

#endif

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
    QObject;

public:
    MainWidget();
    void populateTableData();

    QPushButton *addNewButton;
    QPushButton *logOutButton;
    QPushButton *editButton;

private:
    void createWidgets();
    void initializeTable();
    void createButtons();

    int numSelected;
    LessonsDB lessons;
    QVBoxLayout *mainLayout;
    QPushButton *profileButton;


    QPushButton *deleteButton;

    QTableWidget *mainTable;

public slots:
    void updateTable();
    void toggle(bool checked);
    void deleteItem();
    void selectItem();

signals:
    void edit();
};

#endif

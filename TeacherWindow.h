#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

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


class TeacherWindow : public QDialog
{
    Q_OBJECT

public:
    TeacherWindow();
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

#endif // TEACHERWINDOW_H

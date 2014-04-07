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

private:
    void createWidgets();
    void initializeTable();
    void createButtons();


    LessonsDB lessons;
    QVBoxLayout *mainLayout;
    QPushButton *profileButton;
    QPushButton *logOutButton;

    QTableWidget *mainTable;

public slots:
    void updateTable();

};

#endif // TEACHERWINDOW_H

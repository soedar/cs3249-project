#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include "Lesson.h"
#include "LessonsDB.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLineEdit>
#include <QFormLayout>
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QStringList>
#include <QCheckBox>
#include <QHeaderView>

class TeacherWindow : public QDialog
{
    Q_OBJECT

public:
    TeacherWindow();

private:
    void createWidgets();
    void initializeTable();
    void createButtons();
    void populateTableData();

    LessonsDB *lessons;
    QVBoxLayout *mainLayout;
    QPushButton *profileButton;
    QPushButton *logOutButton;
    QPushButton *addNewButton;
    QTableWidget *mainTable;

};

#endif // TEACHERWINDOW_H

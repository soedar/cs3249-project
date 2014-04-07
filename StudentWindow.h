#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

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
#include <GridButton.h>
#include <QCursor>


class StudentWindow : public QDialog
{
    Q_OBJECT

public:
    StudentWindow();
    void populateTableData();
    QPushButton *logOutButton;

private:
    void createWidgets();
    void initializeTable();
    void createButtons();

    LessonsDB lessons;
    QVBoxLayout *mainLayout;
    QPushButton *profileButton;

    QTableWidget *mainTable;

public slots:
    void updateTable();
    void transition();
    void changeToHand();
    void changeToCursor();

#endif // STUDENTWINDOW_H
};

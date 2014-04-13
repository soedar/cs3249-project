#ifndef STUDENT_MAINWIDGET_H
#define STUDENT_MAINWIDGET_H

#include "MainWidget.h"
#include "GridButton.h"

class StudentMainWidget : public MainWidget
{
    Q_OBJECT;

    public:
        StudentMainWidget();
        QPushButton *editButton;
        void populateTableData();
    private:
        int numSelected;
        QPushButton *deleteButton;
    protected:
        void initializeTable();


    public slots:
        void transition();
        void changeToHand();
        void changeToCursor();
};


#endif
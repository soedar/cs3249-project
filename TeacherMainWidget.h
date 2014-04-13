#ifndef TEACHER_MAINWIDGET_H
#define TEACHER_MAINWIDGET_H

#include "MainWidget.h"

class TeacherMainWidget : public MainWidget
{
    Q_OBJECT;
    public:
        TeacherMainWidget();

        QPushButton *editButton;
        QPushButton *addNewButton;
        void populateTableData();
    private:
        int numSelected;
        QPushButton *deleteButton;
    protected:
        virtual void initializeTable();

    public slots:
        void toggle(bool checked);
        void deleteItem();
        void selectItem();
        void edit();
};


#endif
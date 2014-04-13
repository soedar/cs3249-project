#include "TeacherWindow.h"


TeacherWindow::TeacherWindow()
{
    setGeometry(0,0,800,600);

    mainWidget = new TeacherMainWidget();
    QObject::connect(mainWidget->addNewButton,SIGNAL(clicked()),this,SLOT(toggleAddWidget()));
    toggleMainWidget();
}

void TeacherWindow::toggleAddWidget()
{
    addWidget = new AddLessonWidget();
    QObject::connect(addWidget->uploadBtn, SIGNAL(clicked()), this, SLOT(toggleMainWidget()));
    mainWidget->setParent(0);
    setCentralWidget(addWidget);
}

void TeacherWindow::toggleMainWidget()
{
    setCentralWidget(mainWidget);
    mainWidget->updateTable();
}
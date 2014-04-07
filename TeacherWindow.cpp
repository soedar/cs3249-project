#include "TeacherWindow.h"


TeacherWindow::TeacherWindow()
{
    setGeometry(0,0,650,500);
    lessons = LessonsDBController::getDB();
    createWidgets();
    numSelected = 0;
}

void TeacherWindow::createWidgets()
{
    mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

    createButtons();
    initializeTable();
    populateTableData();

    setLayout(mainLayout);
}

void TeacherWindow::createButtons()
{
    QHBoxLayout *topHeader = new QHBoxLayout;
    topHeader->setAlignment(Qt::AlignRight);

    profileButton = new QPushButton(QIcon(":/assets/profile.png"), tr("My Profile"),this);
    profileButton->setEnabled(true);
    topHeader->addWidget(profileButton);

    logOutButton = new QPushButton(QIcon(":/assets/log_out.png"), tr("Log Out"), this);
    logOutButton->setEnabled(true);
    topHeader->addWidget(logOutButton);

    mainLayout->addLayout(topHeader);

    //addNewButton = new QPushButton;
}
void TeacherWindow::initializeTable()
{
    QHBoxLayout *tableHeader = new QHBoxLayout;
    tableHeader->setAlignment(Qt::AlignCenter);

    QHBoxLayout *tableLeft = new QHBoxLayout;
    tableLeft->setAlignment(Qt::AlignLeft);

    QHBoxLayout *tableRight = new QHBoxLayout;
    tableRight->setAlignment(Qt::AlignRight);

    QHBoxLayout *extraButtons = new QHBoxLayout;
    extraButtons->setAlignment(Qt::AlignRight);

    editButton = new QPushButton(tr("Edit"));
    deleteButton = new QPushButton(tr("Delete"));
    editButton->setEnabled(false);
    deleteButton->setEnabled(false);

    extraButtons->addWidget(editButton);
    extraButtons->addWidget(deleteButton);

    connect(deleteButton,SIGNAL(clicked()),this,SLOT(deleteItem()));


    QLabel *lessonsLabel = new QLabel(tr("Lessons"));
    lessonsLabel->setFont(QFont(NULL, 20));
    lessonsLabel->setAlignment(Qt::AlignLeft);
    lessonsLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    addNewButton = new QPushButton(tr("Add New"));
    addNewButton->setIcon(QIcon(":/assets/new_lesson.png"));
    addNewButton->setEnabled(true);
    tableHeader->addLayout(tableLeft);
    tableHeader->addLayout(tableRight);
    tableRight->addWidget(addNewButton);
    tableLeft->addWidget(lessonsLabel);

    mainLayout->addLayout(tableHeader);

    mainTable = new QTableWidget;
    mainTable->setRowCount(2);
    mainTable->setColumnCount(4);
    QStringList headers;
    headers << "Topic" << "Lessons" << "Date Modified" << "Action";
    mainTable->setHorizontalHeaderLabels(headers);

    QHeaderView *tempHeader = mainTable->horizontalHeader();
    tempHeader->setResizeMode(0, QHeaderView::Stretch);

    QHBoxLayout *table = new QHBoxLayout;
    table->setAlignment(Qt::AlignCenter);
    table->addWidget(mainTable);

    mainLayout->addLayout(extraButtons);

    mainLayout->addLayout(table);
}

void TeacherWindow::populateTableData()
{
    QString tempString;
    Lesson tempLesson;
    QTableWidgetItem *item;
    lessons = LessonsDBController::getDB();

    while (mainTable->rowCount() < lessons.getLessons().size())
    {
        qDebug("adding a new row\n");
        mainTable->insertRow(mainTable->rowCount());
    }
    while (mainTable->rowCount() > lessons.getLessons().size())
    {
        qDebug("removing a row\n");
        mainTable->removeRow(mainTable->rowCount()-1);
    }

    for (int i=0; i<lessons.getLessons().size(); i++)
    {
        tempLesson = lessons.getLessons().at(i);
        tempString = tempLesson.getTopic();
        item = new QTableWidgetItem(tr(tempString.toStdString().c_str()));
        mainTable->setItem(i,0,item);

        tempString = tempLesson.getLesson();
        item = new QTableWidgetItem(tr(tempString.toStdString().c_str()));
        mainTable->setItem(i,1,item);

        tempString = tempLesson.getDate();
        item = new QTableWidgetItem(tr(tempString.toStdString().c_str()));
        mainTable->setItem(i,2,item);
    }

    for (int i=0; i<mainTable->rowCount(); i++)
    {
        QCheckBox *cb = new QCheckBox();
        mainTable->setCellWidget(i,3,cb);
        connect(cb,SIGNAL(toggled(bool)),this,SLOT(toggle(bool)));
    }
}

void TeacherWindow::updateTable()
{
    mainTable->clear();
    populateTableData();
}

void TeacherWindow::deleteItem()
{
    int size = LessonsDBController::getDB().getLessons().size();

    for (int i=size-1; i>=0; i--)
    {
        QCheckBox *box = (QCheckBox *)(mainTable->cellWidget(i,3));
        if (box->isChecked())
        {
            LessonsDBController::deleteItemAt(i);
            numSelected--;
        }
    }
    if (numSelected == 0)
    {
        editButton->setEnabled(false);
        deleteButton->setEnabled(false);
    }
    else if (numSelected == 1)
    {
        editButton->setEnabled(true);
        deleteButton->setEnabled(true);
    }
    else
    {
        editButton->setEnabled(false);
        deleteButton->setEnabled(true);
    }
    updateTable();
}

void TeacherWindow::toggle(bool checked)
{
    if(checked)
    {
        numSelected++;
    }
    else
    {
        numSelected--;
    }
    if (numSelected == 0)
    {
        editButton->setEnabled(false);
        deleteButton->setEnabled(false);
    }
    else if (numSelected == 1)
    {
        editButton->setEnabled(true);
        deleteButton->setEnabled(true);
    }
    else
    {
        editButton->setEnabled(false);
        deleteButton->setEnabled(true);
    }
}

#include "TeacherMainWidget.h"

TeacherMainWidget::TeacherMainWidget()
{
    setGeometry(0, 0, 650, 500);
    numSelected = 0;
    createWidgets();
    qDebug("Teacher Window initialized\n");
}

void TeacherMainWidget::initializeTable()
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
    connect(editButton,SIGNAL(clicked()),this,SLOT(selectItem()));


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
    mainTable->setRowCount(0);
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

void TeacherMainWidget::populateTableData()
{
    QStringList headers;
    headers << "Topic" << "Lessons" << "Date Modified" << "Action";
    mainTable->setHorizontalHeaderLabels(headers);
    QString tempString;
    Lesson tempLesson;
    QTableWidgetItem *item;
    lessons = LessonsDBController::getDB();
    numSelected = 0;

    while (mainTable->rowCount() < lessons.getLessons().size())
    {
        mainTable->insertRow(mainTable->rowCount());
    }
    while (mainTable->rowCount() > lessons.getLessons().size())
    {
        mainTable->removeRow(mainTable->rowCount()-1);
    }

    for (int i=0; i<lessons.getLessons().size(); i++)
    {
        tempLesson = lessons.getLessons().at(i);
        tempString = tempLesson.getTopic();
        item = new QTableWidgetItem(tr(tempString.toStdString().c_str()));
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        mainTable->setItem(i,0,item);

        tempString = tempLesson.getLesson();
        item = new QTableWidgetItem(tr(tempString.toStdString().c_str()));
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        mainTable->setItem(i,1,item);

        tempString = tempLesson.getDate();
        item = new QTableWidgetItem(tr(tempString.toStdString().c_str()));
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        mainTable->setItem(i,2,item);
    }

    for (int i=0; i<mainTable->rowCount(); i++)
    {
        QCheckBox *cb = new QCheckBox();
        mainTable->setCellWidget(i,3,cb);
        connect(cb,SIGNAL(toggled(bool)),this,SLOT(toggle(bool)));
    }
}

void TeacherMainWidget::deleteItem()
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

void TeacherMainWidget::toggle(bool checked)
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

void TeacherMainWidget::selectItem()
{
    if (numSelected != 1)
    {
        return;
    }
    else
    {
        for (int i=0; i<mainTable->rowCount(); i++)
        {
            QCheckBox *box = (QCheckBox *)(mainTable->cellWidget(i,3));
            if (box->isChecked())
            {
                editButton->setEnabled(false);
                deleteButton->setEnabled(false);
                LessonsDBController::setIndex(i);
                qDebug("emitting");
                emit edit();
                return;
            }
        }
    }
}

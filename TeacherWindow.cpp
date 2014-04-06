#include "TeacherWindow.h"


TeacherWindow::TeacherWindow()
{
    setGeometry(0,0,650,500);
    lessons = LessonsDBController::getDB();
    createWidgets();
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

    mainLayout->addLayout(table);
}

void TeacherWindow::populateTableData()
{
    QString tempString;
    Lesson tempLesson = lessons.getLessons().at(0);
    tempString = tempLesson.getTopic();
    QTableWidgetItem *item = new QTableWidgetItem(tr(tempString.toStdString().c_str()));

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
    }
}

QPushButton* TeacherWindow::getAddButton()
{
    return addNewButton;
}

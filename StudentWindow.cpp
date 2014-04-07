#include "StudentWindow.h"
#include "qdebug.h"


StudentWindow::StudentWindow()
{
    setGeometry(0,0,650,500);
    lessons = LessonsDBController::getDB();
    createWidgets();
}

void StudentWindow::createWidgets()
{
    mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

    createButtons();
    initializeTable();
    populateTableData();

    setLayout(mainLayout);
}

void StudentWindow::createButtons()
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
}
void StudentWindow::initializeTable()
{
    QHBoxLayout *tableHeader = new QHBoxLayout;
    tableHeader->setAlignment(Qt::AlignLeft);


    QLabel *lessonsLabel = new QLabel(tr("Available Lessons"));
    lessonsLabel->setFont(QFont(NULL, 20));
    lessonsLabel->setAlignment(Qt::AlignLeft);
    lessonsLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    tableHeader->addWidget(lessonsLabel);

    mainLayout->addLayout(tableHeader);

    mainTable = new QTableWidget;
    mainTable->setRowCount(2);
    mainTable->setColumnCount(3);
    QStringList headers;
    headers << "Topic" << "Lessons" << "Marks";
    mainTable->setHorizontalHeaderLabels(headers);

    QHeaderView *tempHeader = mainTable->horizontalHeader();
    tempHeader->setResizeMode(0, QHeaderView::Stretch);

    QHBoxLayout *table = new QHBoxLayout;
    table->setAlignment(Qt::AlignCenter);
    table->addWidget(mainTable);

    mainLayout->addLayout(table);
}

void StudentWindow::populateTableData()
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
        GridButton *button = new GridButton(this);
        button->setText(tr(tempString.toStdString().c_str()));
        button->setIndex(i);
        button->setEnabled(true);
        connect(button,SIGNAL(leftClicked()),this,SLOT(transition()));
        connect(button,SIGNAL(entered()),this,SLOT(changeToHand()));
        connect(button,SIGNAL(left()),this,SLOT(changeToCursor()));
        mainTable->setCellWidget(i,1,button);

        int marks = tempLesson.getMarks();
        int maxMarks = tempLesson.getMaxMarks();

        tempString = QString::number(marks);
        tempString += "/";
        tempString += QString::number(maxMarks);

        item = new QTableWidgetItem(tr(tempString.toStdString().c_str()));
        mainTable->setItem(i,2,item);
    }


}

void StudentWindow::updateTable()
{
    mainTable->clear();
    populateTableData();
}


void StudentWindow::transition()
{
    GridButton *button = (GridButton *)sender();
    int index = button->getIndex();
    qDebug() << "Index Clicked : " << index << "\n";

}

void StudentWindow::changeToHand()
{
    QWidget::setCursor(Qt::PointingHandCursor);
}

void StudentWindow::changeToCursor()
{
    QWidget::setCursor(Qt::ArrowCursor);
}

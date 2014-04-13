#include "StudentMainWidget.h"

StudentMainWidget::StudentMainWidget()
{
    createWidgets();
}

void StudentMainWidget::initializeTable()
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

void StudentMainWidget::populateTableData()
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
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
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
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        mainTable->setItem(i,2,item);
    }


}

void StudentMainWidget::transition()
{
    GridButton *button = (GridButton *)sender();
    int index = button->getIndex();
    qDebug() << "Index Clicked : " << index << "\n";

}

void StudentMainWidget::changeToHand()
{
    QWidget::setCursor(Qt::PointingHandCursor);
}

void StudentMainWidget::changeToCursor()
{
    QWidget::setCursor(Qt::ArrowCursor);
}

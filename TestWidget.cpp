#include "TestWidget.h"
#include "qdebug.h"


// The test widget contains a test with MCQ questions.
// A teacher can create/edit/delete a test, while
// a student can take the test.
TestWidget::TestWidget(DatabaseLayer *db, QString email)
{
    this->email = email;
    tests = TestsDBController::getDB();
    this->db = db;

    setGeometry(0,0,1000,600);

    questionList = QList<QuestionItem *>();
    menuStudent = new QGroupBox();
    menuTeacher = new QGroupBox();
    vboxStudent = new QVBoxLayout;
    vboxTeacher = new QVBoxLayout;

    testTable = new QTableWidget;
    testTable->setRowCount(0);
    testTable->setColumnCount(1);

    vboxStudent->addWidget(menuStudent);
    vboxStudent->addWidget(testTable);
    vboxTeacher->addWidget(menuTeacher);
    vboxTeacher->addWidget(testTable);

    createMenu();
}

QPair<int, int> TestWidget::getMarks() {
    return qMakePair(marks, questionList.length());
}

void TestWidget::createMenu()
{
    QHBoxLayout *studentLayout = new QHBoxLayout();
    QHBoxLayout *teacherLayout = new QHBoxLayout();


    backButton = new QPushButton(tr("Back to lessons"));
    backButton->setIcon(QIcon(":/assets/left_arrow.png"));
    connect(backButton, SIGNAL(clicked()), this, SLOT(backToLesson()));

    QPushButton *backButtonStudent = new QPushButton(tr("Back to lessons"));
    backButtonStudent->setIcon(QIcon(":/assets/left_arrow.png"));
    connect(backButtonStudent, SIGNAL(clicked()), this, SLOT(backToLesson()));

    studentLayout->addWidget(backButtonStudent);
    teacherLayout->addWidget(backButton);

    saveButton = new QPushButton(tr("Save questions"), this);
    saveButton->setIcon(QIcon(":/assets/save_exit.png"));
    connect(saveButton,SIGNAL(clicked()),this,SLOT(saveTest()));
    teacherLayout->addWidget(saveButton);

    addQnsButton = new QPushButton(tr("Add new question"), this);
    addQnsButton->setIcon(QIcon(":/assets/new_question.png"));
    connect(addQnsButton, SIGNAL(clicked()), this, SLOT(addQuestion()));
    teacherLayout->addWidget(addQnsButton);

    deleteTestButton = new QPushButton(tr("Delete entire test"), this);
    deleteTestButton->setIcon(QIcon(":/assets/delete.png"));
    connect(deleteTestButton, SIGNAL(clicked()), this, SLOT(deleteTest()));
    teacherLayout->addWidget(deleteTestButton);

    deleteQnsButton = new QPushButton(tr("Delete selected questions"), this);
    deleteQnsButton->setIcon(QIcon(":/assets/delete.png"));
    connect(deleteQnsButton, SIGNAL(clicked()), this, SLOT(deleteSelectedQns()));
    deleteQnsButton->setEnabled(false);
    teacherLayout->addWidget(deleteQnsButton);

    marksText = new QLabel(this);
    marksText->setText(QString("Marks from last attempt: %1/%2")
                           .arg(marks).arg(questionList.length()));
    studentLayout->addWidget(marksText);

    menuStudent->setLayout(studentLayout);
    menuTeacher->setLayout(teacherLayout);

}

void TestWidget::setMainLayout()
{
    if (isTeacher)
    {
        setLayout(vboxTeacher);
    }
    else
    {
        marksText->setText(QString("Marks from last attempt: %1/%2")
                           .arg(marks).arg(questionList.length()));
        setLayout(vboxStudent);
    }
}

// PUBLIC SLOTS

void TestWidget::backToLesson()
{
    //TestsDBController::saveTest(index, questionList);

    // remove everything from the table
    questionList.clear();
    //testTable->clear();


    for(int i = testTable->rowCount()-1; i >= 0; i--) {
        testTable->removeCellWidget(i,0);
        testTable->removeCellWidget(i,1);
        testTable->removeRow(i);
    }

    if(isTeacher) {
        emit transitLesson();
    } else {
        testTable->removeColumn(1);
        emit transitLessonStudent();
    }


}

void TestWidget::prepare(bool teacher)
{
    index = LessonsDBController::getIndex();
    tests = TestsDBController::getDB();
    isTeacher = teacher;
    numSelected = 0;

    int width;

    if(isTeacher)
    {
        qDebug("teacher");
        width = 840;
    }
    else
    {
        qDebug("student");
        width = 800;
    }

    testTable->setColumnWidth(0, width);
    marks = MarksDB::getMark(this->email,index);

    if (marks == -1)
    {
        marks = 0;
    }

    setMainLayout();

    questionList = tests->getTest(index);

    QStringList testTableHeader;

    if(isTeacher)
    {
        qDebug("teacher");
        testTable->insertColumn(1);     // to select qns

        for(int i = 0; i < questionList.length(); i++)
        {
           /* QGroupBox *qns = new QGroupBox(this);
            QGridLayout *gridBox = new QGridLayout;
            gridBox->setColumnStretch(1, 2);

            // question name
            QLabel *qnsNameLabel = new QLabel;
            qnsNameLabel->setText("Question:");
            QLineEdit *qnsName = new QLineEdit(questionList[i]->getQnsName());
            gridBox->addWidget(qnsNameLabel, 0, 0);
            gridBox->addWidget(qnsName, 0, 1);

            // option 1
            QLabel *op1Label = new QLabel;
            op1Label->setText("Option 1:");
            QLineEdit *op1 = new QLineEdit(questionList[i]->getOp1());
            gridBox->addWidget(op1Label, 1, 0);
            gridBox->addWidget(op1, 1, 1);

            // option 2
            QLabel *op2Label = new QLabel;
            op2Label->setText("Option 2:");
            QLineEdit *op2 = new QLineEdit(questionList[i]->getOp2());
            gridBox->addWidget(op2Label, 2, 0);
            gridBox->addWidget(op2, 2, 1);

            // option 3
            QLabel *op3Label = new QLabel;
            op3Label->setText("Option 3:");
            QLineEdit *op3 = new QLineEdit(questionList[i]->getOp3());
            gridBox->addWidget(op3Label, 3, 0);
            gridBox->addWidget(op3, 3, 1);

            // option 4
            QLabel *op4Label = new QLabel;
            op4Label->setText("Option 4:");
            QLineEdit *op4 = new QLineEdit(questionList[i]->getOp4());
            gridBox->addWidget(op4Label, 4, 0);
            gridBox->addWidget(op4, 4, 1);

            // answer
            QLabel *ansLabel = new QLabel;
            ansLabel->setText("Answer:");
            QLineEdit *ans = new QLineEdit(QString("%1")
                                           .arg(questionList[i]->getAns()));
            gridBox->addWidget(ansLabel, 5, 0);
            gridBox->addWidget(ans, 5, 1);

            qns->setLayout(gridBox);

            testTable->insertRow(testTable->rowCount());
            testTable->setRowHeight(testTable->rowCount()-1, 200);
            testTable->setCellWidget(testTable->rowCount()-1, 0, qns);*/

            Question *tempQns = new Question();
            tempQns->setQuestion(questionList.at(i));
            tempQns->setLayoutTeacher();

            testTable->insertRow(testTable->rowCount());
            testTable->setRowHeight(testTable->rowCount()-1, 200);
            testTable->setCellWidget(testTable->rowCount()-1,0,tempQns);


            // to select qns and center align the damn checkbox
            QCheckBox *box = new QCheckBox;
            connect(box, SIGNAL(toggled(bool)), this, SLOT(toggle(bool)));
            testTable->setCellWidget(testTable->rowCount()-1, 1, box);
        }

        testTableHeader << "Questions" << "Action";

    }
    else
    {
        qDebug("student");

        // populate table with questions
        for(int i = 0; i < questionList.length(); i++)
        {
            Question *tempQns = new Question();
            tempQns->setQuestion(questionList.at(i));
            tempQns->setLayoutStudent();

            testTable->insertRow(testTable->rowCount());
            testTable->setRowHeight(testTable->rowCount()-1, 200);
            testTable->setCellWidget(testTable->rowCount()-1, 0, tempQns);
        }

        qDebug() << "Ok\n";

        marksText->setText(QString("Marks from last attempt: %1/%2")
                               .arg(marks).arg(questionList.length()));

        // create submit button for student
        submitButton = new QPushButton(tr("Submit"));
        submitButton->setEnabled(true);
        connect(submitButton, SIGNAL(clicked()), this, SLOT(submitTest()));

        testTable->insertRow(testTable->rowCount());
        testTable->setCellWidget(testTable->rowCount()-1, 0, submitButton);

        testTableHeader << "Questions";
    }

    testTable->setHorizontalHeaderLabels(testTableHeader);

    emit prepared();
}

void TestWidget::submitTest()
{
    marks = 0;

    testTable->removeRow(testTable->rowCount()-1);
    testTable->insertColumn(1);
    testTable->setColumnWidth(1, 141);
    testTableHeader << "Questions" << "Results";
    testTable->setHorizontalHeaderLabels(testTableHeader);

    for(int i = 0; i < testTable->rowCount(); i++)
    {
        QLabel *qnsResult = new QLabel(this);
        qnsResult->setAlignment(Qt::AlignCenter);

        Question *tempQns = (Question *)(testTable->cellWidget(i,0));
        if (tempQns->isCorrect())
        {
            qnsResult->setText("CORRECT!");
            marks++;
        }
        else
        {
            int ans = tempQns->getAns();
            qnsResult->setText(QString("WRONG.\nCorrect answer: %1.").arg(ans));
        }

        /*if(questionList[i]->isCorrect())
        {
            qnsResult->setText("CORRECT!");
            marks++;
        } else {
            int ans = questionList[i]->getAns();
            qnsResult->setText(QString("WRONG.\nCorrect answer: %1.").arg(ans));
        }*/

        testTable->setCellWidget(i, 1, qnsResult);
    }

    marksText->setText(QString("Marks from last attempt: %1/%2")
                       .arg(marks).arg(questionList.length()));
    MarksDB::addMark(email,index,marks);

}

void TestWidget::addQuestion()
{
    /*//Question *newQns = new Question();
    QGroupBox *qns = new QGroupBox(this);
    QGridLayout *gridBox = new QGridLayout;
    gridBox->setColumnStretch(1, 2);

    // question name
    QLabel *qnsNameLabel = new QLabel;
    qnsNameLabel->setText("Question:");
    QLineEdit *qnsName = new QLineEdit();
    gridBox->addWidget(qnsNameLabel, 0, 0);
    gridBox->addWidget(qnsName, 0, 1);


    // option 1
    QLabel *op1Label = new QLabel;
    op1Label->setText("Option 1:");
    QLineEdit *op1 = new QLineEdit();
    gridBox->addWidget(op1Label, 1, 0);
    gridBox->addWidget(op1, 1, 1);

    // option 2
    QLabel *op2Label = new QLabel;
    op2Label->setText("Option 2:");
    QLineEdit *op2 = new QLineEdit();
    gridBox->addWidget(op2Label, 2, 0);
    gridBox->addWidget(op2, 2, 1);

    // option 3
    QLabel *op3Label = new QLabel;
    op3Label->setText("Option 3:");
    QLineEdit *op3 = new QLineEdit();
    gridBox->addWidget(op3Label, 3, 0);
    gridBox->addWidget(op3, 3, 1);

    // option 4
    QLabel *op4Label = new QLabel;
    op4Label->setText("Option 4:");
    QLineEdit *op4 = new QLineEdit();
    gridBox->addWidget(op4Label, 4, 0);
    gridBox->addWidget(op4, 4, 1);

    // answer
    QLabel *ansLabel = new QLabel;
    ansLabel->setText("Answer:");
    QLineEdit *ans = new QLineEdit();
    gridBox->addWidget(ansLabel, 5, 0);
    gridBox->addWidget(ans, 5, 1);*/

    Question *qns = new Question();
    questionList.push_back(new QuestionItem());
    qns->setLayoutTeacher();

    testTable->insertRow(testTable->rowCount());
    testTable->setRowHeight(testTable->rowCount()-1, 200);
    testTable->setCellWidget(testTable->rowCount()-1, 0, qns);


    // to select qns and center align the damn checkbox
    QCheckBox *box = new QCheckBox;
    connect(box, SIGNAL(toggled(bool)), this, SLOT(toggle(bool)));
    testTable->setCellWidget(testTable->rowCount()-1, 1, box);

    qDebug("Added");
}

void TestWidget::deleteSelectedQns()
{
    int start = questionList.length()-1;

    qDebug("numSelected = %d", numSelected);

    for(int i = start; i >= 0; i--)
    {
        QCheckBox *box = (QCheckBox *)(testTable->cellWidget(i,1));
        qDebug("qns %d", i+1);

        if(box->isChecked())
        {
            qDebug("is being delected\n");
            testTable->removeCellWidget(i,0);
            testTable->removeRow(i);
            questionList.removeAt(i);
            numSelected--;
        }
    }

    if(numSelected == 0)
    {
        deleteQnsButton->setEnabled(false);
    }
    else
    {
        deleteQnsButton->setEnabled(true);
    }

}

void TestWidget::toggle(bool checked) {
    if(checked) {
        numSelected++;
    } else {
        numSelected--;
    }

    if (numSelected == 0) {
        deleteQnsButton->setEnabled(false);
    } else {
        deleteQnsButton->setEnabled(true);
    }
}

// TODO: add confirmation dialog if there's time
void TestWidget::deleteTest() {
    // confirmation dialog here


    // replace the list of questions with an empty one
    questionList.clear();

    //testTable->clear();

    for(int i = testTable->rowCount()-1; i >= 0; i--) {
        testTable->removeCellWidget(i,0);
        testTable->removeRow(i);
    }

}

void TestWidget::saveTest()
{
    /*QGridLayout *cellLayout;

    // if there's time, call controller to do this instead
    // of accessing question directly.
    for(int i = 0; i < questionList.length(); i++) {
        cellLayout = qobject_cast<QGridLayout *>(testTable->cellWidget(i, 0)->layout());

        // update qns name
        QLineEdit *updatedQns;
        updatedQns = qobject_cast<QLineEdit *>
                (cellLayout->itemAtPosition(0, 1)->widget());
        questionList[i]->setQnsName(updatedQns->text());
        qDebug() << updatedQns->text();

        // update op1
        QLineEdit *updatedOp1;
        updatedOp1 = qobject_cast<QLineEdit *>
                (cellLayout->itemAtPosition(1, 1)->widget());
        questionList[i]->setOp1(updatedOp1->text());
        qDebug() << updatedOp1->text();

        // update op2
        QLineEdit *updatedOp2;
        updatedOp2 = qobject_cast<QLineEdit *>
                (cellLayout->itemAtPosition(2, 1)->widget());
        questionList[i]->setOp2(updatedOp2->text());
        qDebug() << updatedOp2->text();

        // update op3
        QLineEdit *updatedOp3;
        updatedOp3 = qobject_cast<QLineEdit *>
                (cellLayout->itemAtPosition(3, 1)->widget());
        questionList[i]->setOp3(updatedOp3->text());
        qDebug() << updatedOp3->text();

        // update op4
        QLineEdit *updatedOp4;
        updatedOp4 = qobject_cast<QLineEdit *>
                (cellLayout->itemAtPosition(4, 1)->widget());
        questionList[i]->setOp4(updatedOp4->text());
        qDebug() << updatedOp4->text();

        // update ans
        QLineEdit *updatedAns;
        updatedAns = qobject_cast<QLineEdit *>
                (cellLayout->itemAtPosition(5, 1)->widget());
        questionList[i]->setAns(updatedAns->text().toInt());
        qDebug() << updatedAns->text().toInt();

        }*/

    for(int i = 0; i < testTable->rowCount(); i++)
    {
        Question *tempQns = (Question *)(testTable->cellWidget(i,0));
        tempQns->saveQuestion();
        QuestionItem *item = tempQns->getQuestion();
        questionList.removeAt(i);
        questionList.insert(i, item);
    }


    TestsDBController::saveTest(index, questionList);
    LessonsDBController::editMaxMark(index, questionList.size());
    //db->saveTests();
}

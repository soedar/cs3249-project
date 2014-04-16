#include "StudentLessonWidget.h"

StudentLessonWidget::StudentLessonWidget(Lesson *lesson)
{
    setGeometry(0,0,850,600);
    this->lesson = lesson;
    QHBoxLayout *mainLayout = new QHBoxLayout;

    qDebug() << "filelist" << lesson->getFileList();

    textEditWidget = new QTextEdit;
    textEditWidget->setReadOnly(true);

    QStringList fileList = lesson->getFileList();

    if (fileList.count() == 0) {
        textEditWidget->setHtml("<h2>No notes for this lesson</h2>");
    } else {
        QFile htmlFile(fileList.at(0));

        if (!htmlFile.open(QIODevice::ReadWrite)) {
            QMessageBox::information(0, "error", htmlFile.errorString());
            return;
        }

        QString html("");
        QTextStream in(&htmlFile);
        while (!in.atEnd()) {
            html += in.readLine();
        }

        textEditWidget->setHtml(html);
    }


    mainLayout->addWidget(textEditWidget);

    mainLayout->addWidget(new QTextEdit);

    setLayout(mainLayout);

    this->menuWidget = new MenuWidget(this, lesson);
    this->menuWidget->show();
}


void StudentLessonWidget::resizeEvent(QResizeEvent *event) 
{
    this->menuWidget->adjustSize();
}
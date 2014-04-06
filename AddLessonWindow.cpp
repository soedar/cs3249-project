#include "AddLessonWindow.h"

AddLessonWindow::AddLessonWindow()
{
    setGeometry(0,0,650,500);
    setAcceptDrops(true);
    createWidgets();
}

void AddLessonWindow::createWidgets()
{
   uploader = new ImageUploader(this);
   mainLayout = new QVBoxLayout();

   QLabel *addNewLabel = new QLabel(tr("Add New Lesson"));
   addNewLabel->setFont(QFont(NULL, 16));
   addNewLabel->setAlignment(Qt::AlignCenter);
   addNewLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

   QHBoxLayout *titleHeader = new QHBoxLayout();
   titleHeader->setAlignment(Qt::AlignCenter);

   titleHeader->addWidget(addNewLabel);

   QHBoxLayout *topHeader = new QHBoxLayout();
   topHeader->setAlignment(Qt::AlignCenter);

   QHBoxLayout *topLeftHeader = new QHBoxLayout();
   topLeftHeader->setAlignment(Qt::AlignCenter);

   QHBoxLayout *topRightHeader = new QHBoxLayout();
   topRightHeader->setAlignment(Qt::AlignCenter);

   QLabel *titleLabel = new QLabel(tr("Title : "));
   QLabel *topicLabel = new QLabel(tr("Topic : "));

   lessonName = new QLineEdit();
   lessonName->setFixedSize(220,30);
   lessonName->setMaxLength(50);

   topicName = new QComboBox();
   topicName->setFixedSize(220,30);
   LessonsDB ldb = LessonsDBController::getDB();
   QStringList list = ldb.getTopics();
   topicName->addItems(list);

   topLeftHeader->addWidget(titleLabel);
   topLeftHeader->addWidget(lessonName);

   topRightHeader->addWidget(topicLabel);
   topRightHeader->addWidget(topicName);

   topHeader->addLayout(topLeftHeader);
   topHeader->addLayout(topRightHeader);

   QHBoxLayout *mainArea = new QHBoxLayout();
   uploadImages = new QLabel(tr("Upload Images"));
   uploadFiles = new QLabel(tr("Upload Files"));

   mainArea->addWidget(uploader);

   mainLayout->addLayout(titleHeader);
   mainLayout->addLayout(topHeader);
   mainLayout->addLayout(mainArea);
   setLayout(mainLayout);

}

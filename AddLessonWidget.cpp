#include "AddLessonWidget.h"

//The window that allows u to create a new lesson
AddLessonWidget::AddLessonWidget()
{
    setGeometry(0,0,650,500);
    setAcceptDrops(true);
    createWidgets();
}

void AddLessonWidget::createWidgets()
{

   uploader = new ImageUploader(this);
   uploaderF = new FileUploader(this);
   mainLayout = new QVBoxLayout();

   //Contains the title
   QHBoxLayout *titleHeader = new QHBoxLayout();

   //Contain the lessonName, topic Name stuff
   QHBoxLayout *topHeader = new QHBoxLayout();
   QHBoxLayout *topLeftHeader = new QHBoxLayout();
   QHBoxLayout *topRightHeader = new QHBoxLayout();


   //Contain the file/image uploaders
   QHBoxLayout *mainArea = new QHBoxLayout();
   QVBoxLayout *mainAreaLeft = new QVBoxLayout();
   QVBoxLayout *mainAreaRight = new QVBoxLayout();

   QVBoxLayout *mainAreaCenter = new QVBoxLayout();

   //For the exit button
   QHBoxLayout *bottomLayout = new QHBoxLayout();

   titleHeader->setAlignment(Qt::AlignCenter);

   topHeader->setAlignment(Qt::AlignCenter);
   topLeftHeader->setAlignment(Qt::AlignCenter);
   topRightHeader->setAlignment(Qt::AlignCenter);

   mainArea->setAlignment(Qt::AlignCenter);
   mainAreaLeft->setAlignment(Qt::AlignCenter);
   mainAreaRight->setAlignment(Qt::AlignCenter);

   bottomLayout->setAlignment(Qt::AlignCenter);

   QLabel *addNewLabel = new QLabel(tr("Add New Lesson"));
   addNewLabel->setFont(QFont(NULL, 16));
   addNewLabel->setAlignment(Qt::AlignCenter);
   addNewLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

   titleHeader->addWidget(addNewLabel);

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

   uploadImages = new QLabel(tr("Upload Images"));
   uploadFiles = new QLabel(tr("Upload Files"));

   QFrame* line = new QFrame();
   line->setFrameShape(QFrame::VLine);
   line->setFrameShadow(QFrame::Sunken);

   dragImages = new QPushButton(QIcon(":/assets/diagrams.png"), tr("Drag Images to Upload!"));
   dragImages->setFlat(true);
   dragImages->setEnabled(false);
   dragFiles = new QPushButton(QIcon(":/assets/pdf.png"), tr("Drag PDF Files to Upload!"));
   dragFiles->setFlat(true);
   dragFiles->setEnabled(false);

   uploadBtn = new QPushButton(tr("Done"));

   mainAreaLeft->addWidget(uploadImages);
   mainAreaLeft->addWidget(uploader);
   mainAreaLeft->addWidget(dragImages);

   mainAreaCenter->addWidget(line);

   mainAreaRight->addWidget(uploadFiles);
   mainAreaRight->addWidget(uploaderF);
   mainAreaRight->addWidget(dragFiles);

   mainArea->addLayout(mainAreaLeft);
   mainArea->addLayout(mainAreaCenter);
   mainArea->addLayout(mainAreaRight);

   bottomLayout->addWidget(uploadBtn);

   mainLayout->addLayout(titleHeader);
   mainLayout->addLayout(topHeader);
   mainLayout->addLayout(mainArea);
   mainLayout->addLayout(bottomLayout);

   setLayout(mainLayout);

   connect(uploadBtn,SIGNAL(clicked()),this,SLOT(addStuff()));

}

void AddLessonWidget::addStuff()
{
    if (lessonName->text().length() > 0)
    {
        LessonsDBController::addLesson(lessonName->text(), topicName->currentText(), uploaderF->getList(), uploader->getList());
        qDebug() << "Num Files : " << uploaderF->getList()->size() << "   Num Images : " << uploader->getList()->size() << "\n";
    }
    lessonName->clear();
    uploaderF->clearData();
    uploader->clearData();
}

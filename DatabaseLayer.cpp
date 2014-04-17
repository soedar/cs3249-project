#include "DatabaseLayer.h"
#include <QDesktopServices>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QtDebug>

DatabaseLayer::DatabaseLayer()
{
    dataPath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QDir dataDir(dataPath);
    dataDir.mkpath(dataPath);

    ldb = new LessonsDBController();
    ldb->init();
    mdb = new MarksDB();

    initTimer();

    //lessonsDataPath = ":";

    qDebug() << "Data path is: " << dataPath;

    preloadUsers();
    loadAllUsers();

    connect(LessonsDBController::getDB(), SIGNAL(newLessonCreated()), this, SLOT(saveNewLesson()));
}

void DatabaseLayer::saveNewLesson()
{
    saveLessons();
    QFile updateFile(updateDatabaseFile());
    if (!updateFile.open(QIODevice::ReadWrite | QIODevice::Append)) {
        QMessageBox::information(0, "error", updateFile.errorString());
        return;
    }

    QTextStream out(&updateFile);
    out << "new_lesson" << endl;
    updateFile.close();
}

void DatabaseLayer::initTimer()
{
    updateCount = 0;

    QFile updateFile(updateDatabaseFile());
    if (!updateFile.exists()) {
        if (!updateFile.open(QIODevice::WriteOnly)) {
            QMessageBox::information(0, "error", updateFile.errorString());
            return;
        }
        QTextStream out(&updateFile);
        out << "updates" << endl;
        updateCount = 1;
    } else {
        if (!updateFile.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", updateFile.errorString());
            return;
        }
        QTextStream in(&updateFile);
        while (!in.atEnd()) {
            in.readLine();
            updateCount++;
        }
    }
    updateFile.close();

    pollTimer = new QTimer(0);
    connect(pollTimer, SIGNAL(timeout()), this, SLOT(checkDbUpdate()));
    pollTimer->start(1000);
}

void DatabaseLayer::checkDbUpdate()
{
    QFile updateFile(updateDatabaseFile());
    if (!updateFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", updateFile.errorString());
        return;
    }

    int newUpdateCount = 0;
    QString lastUpdate;
    QTextStream in(&updateFile);
    while (!in.atEnd()) {
        newUpdateCount++;
        lastUpdate = in.readLine();
    }

    // Has a new update
    if (newUpdateCount > updateCount) {
        qDebug() << "has new update";
        if (lastUpdate == "new_lesson") {
            emit newLessonCreated();
        }
    }
    updateCount = newUpdateCount;

}

void DatabaseLayer::preloadUsers()
{
    QFile userFile(userDatabaseFile());
    if (!userFile.exists()) {
        if (!userFile.open(QIODevice::WriteOnly)) {
            QMessageBox::information(0, "error", userFile.errorString());
            return;
        }
        QTextStream out(&userFile);
        out << "teacher:11111:2" << endl;
        out << "student:11111:1" << endl;
    }
    userFile.close();
}

QString DatabaseLayer::userDatabaseFile()
{
    QString path = dataPath + "/users.db";
    return QDir::toNativeSeparators(path);
}

QString DatabaseLayer::lessonsDatabaseFile()
{
    QString path = dataPath + "/lessons.db";
    return QDir::toNativeSeparators(path);
}

QString DatabaseLayer::marksDatabaseFile()
{
    QString path = dataPath + "/marks.db";
    return QDir::toNativeSeparators(path);
}

QString DatabaseLayer::updateDatabaseFile()
{
    QString path = dataPath + "/updates.txt";
    return QDir::toNativeSeparators(path);
}

User DatabaseLayer::userWithEmail(const QString &email)
{
    if (users.contains(email)) {
        return users[email];
    }

    return User();
}

void DatabaseLayer::loadAllUsers()
{
    QFile userFile(userDatabaseFile());

    if (!userFile.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", userFile.errorString());
        return;
    }

    QTextStream in(&userFile);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList data = line.split(":");

        QString email = data[0];
        QString password = data[1];
        UserRole role = static_cast<UserRole>(data[2].toInt());

        if (!users.contains(email)) {
            User user(email, password, role);
            if (user.userRole() == UserRoleStudent)
            {

            }
            users.insert(email, user);
        }
    }
    userFile.close();
}

void DatabaseLayer::saveLessons()
{
    qDebug() << "SAVING\n";
    QFile lessonFile(lessonsDatabaseFile());

    if (!lessonFile.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QMessageBox::information(0, "error", lessonFile.errorString());
        return;
    }
    LessonsDB *ldb = LessonsDBController::getDB();
    int numLessons = ldb->getLessons().size();


    QTextStream out(&lessonFile);
    out << numLessons << endl;

    /**
     * Format (separator will be "whitspace,whitespace"
     *
     * Number of Lessons
     * isTeacher (0 or 1) , LessonName , TopicName , Date , Marks , MaxMarks
     * FileList length
     * Files
     * ImageList Length
     * Images
     * Number Of Custom Images
     * Number of annotations for CI 1
     * Annotations
     * POS1 POS2
     * Text
     * Number of annotations for CI 2
     * Annotations
     * .
     * .
     * .
     */

    for (int i=0; i<numLessons; i++)
    {
        Lesson lesson = ldb->getLessons().at(i);
        int isTeacher;
        if (lesson.isTeacher())
        {
            isTeacher = 1;
        }
        else
        {
            isTeacher = 0;
        }

        out << isTeacher << " , " << lesson.getLesson() << " , " << lesson.getTopic() << " , ";
        out << lesson.getDate() << " , "  << lesson.getMaxMarks() << endl;

         qDebug("Part 1 OK\n");

        out << lesson.getFileList().size() << endl;

        qDebug() << lesson.getFileList().size() << "\n";

        for (int j=0; j<lesson.getFileList().size(); j++)
        {
            out << lesson.getFileList().at(j) << endl;
            qDebug() << "2." << j << "\n";
        }

        qDebug("Part 2 OK\n");

        out << lesson.getImageList().size() << endl;

        qDebug() << lesson.getImageList().size() << "\n";

        for (int j=0; j<lesson.getImageList().size(); j++)
        {
            out << lesson.getImageList().at(j) << endl;
            qDebug() << "3." << j << "\n";
        }

        qDebug("Part 3 OK\n");

        out << lesson.getAnnos().size() << endl;

        for (int j=0; j<lesson.getAnnos().size(); j++)
        {
            out << lesson.getAnnos().at(j)->getAnnos().size() << endl;

            for (int k=0; k<lesson.getAnnos().at(j)->getAnnos().size(); k++)
            {
                AnnotationGraphicsItem *agi = lesson.getAnnos().at(j)->getAnnos().at(k);
                out << agi->boxRect->pos().x() << " , " << agi->boxRect->pos().y() << " , ";
                out << agi->lineRect->pos().x() << " , " << agi->lineRect->pos().y() << endl;
                out << agi->box->toPlainText() << endl;
                qDebug() << "4." << j << "." << k << "\n";
            }
        }

         qDebug("Part 4 OK\n");
    }
    lessonFile.close();
}

void DatabaseLayer::loadLessons()
{
    qDebug() << "READING\n";
    ldb->clear();
    QFile lessonFile(lessonsDatabaseFile());

    if (!lessonFile.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", lessonFile.errorString());
        return;
    }

    QTextStream in(&lessonFile);

    //First line
    int numLessons = in.readLine().toInt();

    int temp;
    bool isTeacher;
    QString lessonName;
    QString topicName;
    QString date;
    int maxMarks;
    int numFiles;
    int numImages;
    QStringList *fileList = new QStringList();
    QStringList *imageList = new QStringList();
    int numCIs;
    int numAnnos;
    QList<CustomImage *> ciList = QList<CustomImage *>();
    QList<int> numbers = QList<int>();
    QList<QPointF> positions = QList<QPointF>();
    QStringList *annoText = new QStringList();


    for (int i=0; i<numLessons; i++)
    {
        fileList = new QStringList();
        imageList = new QStringList();
        ciList = QList<CustomImage *>();
        numbers = QList<int>();
        positions = QList<QPointF>();
        annoText = new QStringList();

        //Second line
        QString line = in.readLine();
        QStringList data = line.split(" , ");
        temp = data.at(0).toInt();
        if (temp == 0)
        {
            isTeacher = false;
        }
        else
        {
            isTeacher = true;
        }
        lessonName = data.at(1);
        topicName = data.at(2);
        date = data.at(3);
        maxMarks = data.at(4).toInt();

        qDebug("Part 1 OK\n");

        //Third line
        numFiles = in.readLine().toInt();

        for (int j=0; j<numFiles; j++)
        {
            //Lines 3.1 to 3.j
            fileList->push_back(in.readLine());
        }

        qDebug("Part 2 OK\n");


        //Fourth line
        numImages = in.readLine().toInt();



        for (int j=0; j<numImages; j++)
        {
            //Lines 4.1 to 4.j
            imageList->push_back(in.readLine());
        }
         qDebug("Part 3 OK\n");

        //Fifth line
        numCIs = in.readLine().toInt();

        for (int j=0; j<numCIs; j++)
        {
            CustomImage *image = new CustomImage();
            ciList.push_back(image);
            numAnnos = in.readLine().toInt();
            numbers.push_back(numAnnos);
            for (int k=0; k<numAnnos; k++)
            {
                QString lineCI = in.readLine();
                QStringList dataCI = lineCI.split(" , ");
                qDebug() << "DataCI.size " << dataCI.size() << "\n";
                positions.push_back(QPointF(dataCI.at(0).toFloat(), dataCI.at(1).toFloat()));
                positions.push_back(QPointF(dataCI.at(2).toFloat(), dataCI.at(3).toFloat()));
                annoText->push_back(in.readLine());
            }
        }
        qDebug("Part 4 OK\n");
        LessonsDBController::addLesson(isTeacher,lessonName,topicName,date,maxMarks,fileList,imageList,ciList,numbers,positions,annoText);

    }

    lessonFile.close();
}

void DatabaseLayer::saveMarks()
{
    qDebug() << "SAVING MARKS\n";
    QFile marksFile(marksDatabaseFile());

    if (!marksFile.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QMessageBox::information(0, "error", marksFile.errorString());
        return;
    }

    QTextStream out(&marksFile);

    QMap<QString,QMap<int,int> > map = mdb->getData();

    QList<QString> listStudents = map.uniqueKeys();

    for (int i=0;i<listStudents.size(); i++)
    {
        QString name = listStudents.at(i);

        QMap<int,int> tempMap = map.value(name);
        QList<int> lessonIds = tempMap.uniqueKeys();

        for (int j=0; j<lessonIds.size(); j++)
        {
            int lesson = lessonIds.at(j);
            int mark = tempMap.value(lesson);

            out << name << " , " << lesson << " , " << mark << endl;
        }
    }
    marksFile.close();

}

void DatabaseLayer::loadMarks()
{

    QFile marksFile(marksDatabaseFile());

    if (!marksFile.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", marksFile.errorString());
        return;
    }

    QTextStream in(&marksFile);

    MarksDB::clear();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList data = line.split(" , ");

        QString email = data[0];
        int lessonId = data[1].toInt();
        int mark = data[2].toInt();
        MarksDB::addMark(email,lessonId,mark);
    }
    marksFile.close();
}

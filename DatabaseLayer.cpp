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

    //lessonsDataPath = ":";

    qDebug() << "Data path is: " << dataPath;

    preloadUsers();
    loadAllUsers();
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
        out << "student:11111:1";
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
            users.insert(email, user);
        }
    }
    userFile.close();
}

void DatabaseLayer::saveLessons()
{
    QFile lessonFile(lessonsDatabaseFile());

    if (!lessonFile.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", lessonFile.errorString());
        return;
    }
    LessonsDB ldb = LessonsDBController::getDB();
    int numLessons = ldb.getLessons().size();

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
     * Number of annotations for CI 2
     * Annotations
     * .
     * .
     * .
     */

    for (int i=0; i<numLessons; i++)
    {
        Lesson lesson = ldb.getLessons().at(i);
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
        out << lesson.getDate() << " , " << lesson.getMarks() << " , " << lesson.getMaxMarks() << endl;

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
                qDebug() << "4." << j << "." << k << "\n";
            }
        }

         qDebug("Part 4 OK\n");
    }
    lessonFile.close();
}

void DatabaseLayer::loadLessons()
{
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
    int marks;
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


    for (int i=0; i<numLessons; i++)
    {
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
        marks = data.at(4).toInt();
        maxMarks = data.at(5).toInt();

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
            }
        }
        qDebug("Part 4 OK\n");
        LessonsDBController::addLesson(isTeacher,lessonName,topicName,date,marks,maxMarks,fileList,imageList,ciList,numbers,positions);

    }

    lessonFile.close();
}

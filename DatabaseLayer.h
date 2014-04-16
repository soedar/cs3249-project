#ifndef DB_LAYER_H
#define DB_LAYER_H

#include <QString>
#include <QMap>
#include <QObject>
#include <QTimer>
#include "User.h"
#include "LessonsDBController.h"
#include "MarksDB.h"

class DatabaseLayer : public QObject 
{

    Q_OBJECT

public:
    DatabaseLayer();
    User userWithEmail(const QString &);
    LessonsDBController *ldb;
    MarksDB *mdb;
    void saveLessons();
    void loadLessons();
    void saveMarks();
    void loadMarks();
private:
    QString dataPath;
    //QString lessonsDataPath;
    QMap<QString, User> users;
    QTimer *pollTimer;
    int updateCount;

    void initTimer();
    void loadAllUsers();
    void preloadUsers();
    QString userDatabaseFile();
    QString lessonsDatabaseFile();
    QString updateDatabaseFile();
    QString marksDatabaseFile();

signals:
    void newLessonCreated();

private slots:
    void checkDbUpdate();
    void saveNewLesson();

};

#endif

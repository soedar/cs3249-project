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

    qDebug() << "Data path is: " << dataPath;

    loadAllUsers();
}

QString DatabaseLayer::userDatabaseFile()
{
    QString path = dataPath + "/users.db";
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
}
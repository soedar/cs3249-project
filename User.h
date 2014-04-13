#ifndef USER_H
#define USER_H

#include <QString>

typedef enum
{
    UserRoleNone    = 0,
    UserRoleStudent = 1,
    UserRoleTeacher = 2,
    UserRoleAdmin   = 3
} UserRole;

class User
{
public:
    User();
    User(const QString &email, const QString &password, UserRole userRole);

    QString email();
    QString password();
    UserRole userRole();

private:
    QString _email;
    QString _password;
    UserRole _userRole;
};

#endif
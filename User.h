#ifndef USER_H
#define USER_H

#include <QString>

typedef enum
{
    UserRoleNone,
    UserRoleStudent,
    UserRoleTeacher,
    UserRoleAdmin
} UserRole;

class User
{
public:
    User();
    User(const QString &email, const QString &password);

    QString email();
    QString password();
    UserRole userRole();

private:
    QString _email;
    QString _password;
    UserRole _userRole;
};

#endif
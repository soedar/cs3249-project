#include "User.h"

User::User()
{
    this->_userRole = UserRoleNone;
}

User::User(const QString &email, const QString &password, UserRole userRole)
{
    this->_email = email;
    this->_password = password;
    this->_userRole = userRole;
}

QString User::email()
{
    return this->_email;
}

QString User::password()
{
    return this->_password;
}

UserRole User::userRole()
{
    return this->_userRole;
}
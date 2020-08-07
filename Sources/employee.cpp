/**************************************************************************
作者: wen
日期: 2020-08-05
**************************************************************************/

#include "./Headers/employee.h"

Employee::Employee()
{

}

QString Employee::getName() const
{
    return name;
}

void Employee::setName(const QString &value)
{
    name = value;
}

QString Employee::getPassword() const
{
    return password;
}

void Employee::setPassword(const QString &value)
{
    password = value;
}

QString Employee::getUsername() const
{
    return username;
}

void Employee::setUsername(const QString &value)
{
    username = value;
}

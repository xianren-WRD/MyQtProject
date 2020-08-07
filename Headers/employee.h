#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

//员工类 -- 相关set方法没有用到，因为使用的QList的at方法返回的是const对象
class Employee
{
public:
    Employee();
    Employee(QString name,QString username,QString password):name(name),username(username),password(password){}

    QString getName() const;
    void setName(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getUsername() const;
    void setUsername(const QString &value);

private:
    QString name;
    QString username;
    QString password;
};

#endif // EMPLOYEE_H

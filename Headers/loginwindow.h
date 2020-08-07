#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include "administratorwindow.h"
#include "staffwindow.h"
#include "dataprocessing.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginWindow *ui;
    AdministratorWindow *admin;
    StaffWindow *staff;
    int count;//登录失败count次后，退出程序
};

#endif // LOGINWINDOW_H

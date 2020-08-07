#ifndef STAFFMANAGEMENTWINDOW_H
#define STAFFMANAGEMENTWINDOW_H

#include <QMainWindow>
#include "registrationwindow.h"
#include "dataprocessing.h"

namespace Ui {
class StaffManagementWindow;
}

class StaffManagementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StaffManagementWindow(QWidget *parent = nullptr);
    ~StaffManagementWindow();

private slots:
    void showMain();

    void on_addpushButton_clicked();

    void on_deletepushButton_clicked();

    void on_updatepushButton_clicked();

    void on_returnpushButton_clicked();

    void on_tableWidget_cellClicked();

signals:
    void backToMain();

private:
    Ui::StaffManagementWindow *ui;
    RegistrationWindow *registration;
};

#endif // STAFFMANAGEMENTWINDOW_H

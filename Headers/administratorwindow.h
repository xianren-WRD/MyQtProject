#ifndef ADMINISTRATORWINDOW_H
#define ADMINISTRATORWINDOW_H

#include <QMainWindow>
#include "cargowindow.h"
#include "staffmanagementwindow.h"
#include "cargomanagementwindow.h"

namespace Ui {
class AdministratorWindow;
}

class AdministratorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorWindow(QWidget *parent = nullptr);
    ~AdministratorWindow();

private slots:
    void on_staffpushButton_clicked();

    void on_cargopushButton_clicked();

    void backFormStaffManage();

    void backFormCargoManage();

private:
    Ui::AdministratorWindow *ui;
    StaffManagementWindow *staffManagement;
    CargoManagementWindow *cargoManagement;
};

#endif // ADMINISTRATORWINDOW_H

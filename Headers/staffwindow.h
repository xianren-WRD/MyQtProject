#ifndef STAFFWINDOW_H
#define STAFFWINDOW_H

#include <QMainWindow>
#include "cargomanagementwindow.h"
#include "shoppingwindow.h"

namespace Ui {
class StaffWindow;
}

class StaffWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StaffWindow(QWidget *parent = nullptr);
    ~StaffWindow();

private slots:
    void on_shoppingButton_clicked();

    void on_inquireButton_clicked();

    void backFromCargo();

    void backFromShop();

private:
    Ui::StaffWindow *ui;
    CargoManagementWindow *cargoManagement;
    ShoppingWindow *shopping;
};

#endif // STAFFWINDOW_H

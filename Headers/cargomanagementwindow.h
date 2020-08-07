#ifndef CARGOMANAGEMENTWINDOW_H
#define CARGOMANAGEMENTWINDOW_H

#include <QMainWindow>
#include "cargowindow.h"

namespace Ui {
class CargoManagementWindow;
}

class CargoManagementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CargoManagementWindow(QWidget *parent = nullptr);
    ~CargoManagementWindow();

public slots:
    void showMain();

public slots:
    //设置采购按键，并绑定采购处理的槽函数
    void addPurchaseButton();
    //设置结算按键，并绑定结算处理的槽函数
    void addPurchaseSettleButton();

private slots: 
    void on_returnpushButton_clicked();

    void on_updatepushButton_clicked();

    void on_addAllButton_clicked();//将库存所有的商品，以默认的售价全数量上架销售

    void on_putButton_clicked();

    void on_deleteButton_clicked();

    void on_salesTableWidget_cellClicked();

    void on_purchaseTableWidget_cellClicked();
    //采购功能槽函数
    void purchaseButtonClicked();
    //结算功能槽函数
    void purchaseSettleButtonClicked();

signals:
    void backToMain();

private:
    Ui::CargoManagementWindow *ui;
    CargoWindow *purchaseCargo;
    CargoWindow *putCargo;
};

#endif // CARGOMANAGEMENTWINDOW_H

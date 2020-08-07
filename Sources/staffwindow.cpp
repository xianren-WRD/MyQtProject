/**************************************************************************
作者: wen
日期: 2020-08-05
描述: 点击不同按键，跳转到货物管理界面或者结算界面。员工的货物管理界面在货物管理界面的
      基础上，使用了货物管理界面的增加结算按键功能和结算采购商品的功能。
      所以员工的货物管理界面有一部分和管理员界面相同。
**************************************************************************/

#include "./Headers/staffwindow.h"
#include "ui_staffwindow.h"
#include <QDebug>

StaffWindow::StaffWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StaffWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1050,800);
    this->setWindowTitle("员工界面");

    cargoManagement = new CargoManagementWindow(this);
    connect(cargoManagement,&CargoManagementWindow::backToMain,this,&StaffWindow::backFromCargo);

    shopping = new ShoppingWindow(this);
    connect(shopping,&ShoppingWindow::back,this,&StaffWindow::backFromShop);
}

StaffWindow::~StaffWindow()
{
    qDebug() << "~StaffWindow()";
    delete ui;
}

void StaffWindow::on_shoppingButton_clicked()
{
    shopping->show();
    this->hide();
}

void StaffWindow::on_inquireButton_clicked()
{  
    cargoManagement->show();
    cargoManagement->addPurchaseSettleButton();
    this->hide();
}

void StaffWindow::backFromCargo()
{
    this->show();
    cargoManagement->hide();
}

void StaffWindow::backFromShop()
{
    this->show();
    shopping->hide();
}

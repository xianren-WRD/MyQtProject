/**************************************************************************
作者: wen
日期: 2020-08-05
描述: 点击不同按键，跳转到货物管理界面或者员工管理界面。管理员的货物管理界面在货物管理
      界面的基础上，使用了货物管理界面的增加采购按键功能和采购商品功能。
      也就是说管理员和员工的货物管理界面有一部分是相同的。
**************************************************************************/

#include "./Headers/administratorwindow.h"
#include "ui_administratorwindow.h"
#include <QDebug>

AdministratorWindow::AdministratorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1050,800);
    this->setWindowTitle("管理员界面");

    staffManagement = new StaffManagementWindow;
    cargoManagement = new CargoManagementWindow;
    connect(staffManagement,&StaffManagementWindow::backToMain,this,&AdministratorWindow::backFormStaffManage);
    connect(cargoManagement,&CargoManagementWindow::backToMain,this,&AdministratorWindow::backFormCargoManage);
}

AdministratorWindow::~AdministratorWindow()
{
    qDebug() << "~AdministratorWindow()";
    delete ui;
    delete cargoManagement;
    delete staffManagement;
}

void AdministratorWindow::on_staffpushButton_clicked()
{
    staffManagement->show();
    this->hide();
}

void AdministratorWindow::on_cargopushButton_clicked()
{
    cargoManagement->show();
    cargoManagement->addPurchaseButton();
    this->hide();
}

void AdministratorWindow::backFormStaffManage()
{
    this->show();
    staffManagement->hide();
}

void AdministratorWindow::backFormCargoManage()
{
     this->show();
     cargoManagement->hide();
}

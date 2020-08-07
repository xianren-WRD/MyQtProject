/**************************************************************************
作者: wen
日期: 2020-08-05
描述: 读取员工信息文本，按下更新按钮后显示在控件上。可以删除选中的员工账户，也可以增加
      新的员工账户。但是员工信息不能通过点击条目进行修改。
**************************************************************************/

#include "./Headers/staffmanagementwindow.h"
#include "ui_staffmanagementwindow.h"
#include <QDebug>

StaffManagementWindow::StaffManagementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StaffManagementWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1050,800);
    this->setWindowTitle("员工管理");

    QStringList header;
    header << "姓名" << "用户名" << "密码";
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setFixedWidth(4*ui->tableWidget->width());
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->deletepushButton->setEnabled(false);

    registration = new RegistrationWindow(this);
    connect(registration,&RegistrationWindow::back,this,&StaffManagementWindow::showMain);
}

StaffManagementWindow::~StaffManagementWindow()
{
    qDebug() << "~StaffManagementWindow()";
    delete ui;
}

void StaffManagementWindow::showMain()
{
    this->show();
}

void StaffManagementWindow::on_addpushButton_clicked()
{
    registration->show();
    this->hide();
}

void StaffManagementWindow::on_deletepushButton_clicked()
{
    int ret = QMessageBox::information(this,"提示","是否要删除该账户", QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(QMessageBox::No == ret)
    {
        return;
    }

    QTableWidgetItem *item = ui->tableWidget->currentItem();
    int row = item->row();
    DataProcessing::employeelist.removeAt(row);
    ui->tableWidget->removeRow(row);
    DataProcessing::generateJsonData(EmployeeType);

    ui->deletepushButton->setEnabled(false);
    QMessageBox::information(this,"提示","删除成功");
}

void StaffManagementWindow::on_updatepushButton_clicked()
{
    ui->tableWidget->setRowCount(DataProcessing::employeelist.size());
    for(int i = 0; i < DataProcessing::employeelist.size(); i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(DataProcessing::employeelist.at(i).getName()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(DataProcessing::employeelist.at(i).getUsername()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(DataProcessing::employeelist.at(i).getPassword()));
    }
}

void StaffManagementWindow::on_returnpushButton_clicked()
{
    emit backToMain();
}

void StaffManagementWindow::on_tableWidget_cellClicked()
{
    ui->deletepushButton->setEnabled(true);
}

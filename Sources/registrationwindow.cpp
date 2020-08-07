/**************************************************************************
作者: wen
日期: 2020-08-05
描述: 注册新的员工账户，并追加写入员工信息文本中。可以连续注册，结束注册3s后回到上一界面
**************************************************************************/

#include "./Headers/registrationwindow.h"
#include "ui_registrationwindow.h"
#include <QDebug>

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1050,800);
    this->setWindowTitle("注册新员工");
}

RegistrationWindow::~RegistrationWindow()
{
    qDebug() << "~RegistrationWindow()";
    delete ui;
}

void RegistrationWindow::on_registrationButton_clicked()
{
    if(ui->namelineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"无法注册","请输入员工姓名");
        return;
    }

    if(ui->usernamelineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"无法注册","请输入用户名");
        return;
    }

    if(ui->passwordlineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"无法注册","请输入密码");
        return;
    }

    if("root" == ui->usernamelineEdit->text())
    {
        QMessageBox::information(this,"无法注册","该账户已经被注册，请您重新注册。");
        ui->namelineEdit->clear();
        ui->usernamelineEdit->clear();
        ui->passwordlineEdit->clear();
        return;
    }

    for(int i = 0; i < DataProcessing::employeelist.size(); i++)
    {
        if(ui->usernamelineEdit->text() == DataProcessing::employeelist.at(i).getUsername())
        {
            QMessageBox::information(this,"无法注册","该账户已经被注册，请您重新注册。");
            ui->namelineEdit->clear();
            ui->usernamelineEdit->clear();
            ui->passwordlineEdit->clear();
            return;
        }
    }

    DataProcessing::employeelist.insert(DataProcessing::employeelist.size(),
                                        Employee(ui->namelineEdit->text(),ui->usernamelineEdit->text(),ui->passwordlineEdit->text()));
    DataProcessing::generateJsonData(EmployeeType);

    int ret = QMessageBox::information(this,"提示","注册成功,是否需要继续注册", QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    ui->namelineEdit->clear();
    ui->usernamelineEdit->clear();
    ui->passwordlineEdit->clear();

    switch (ret)
    {
    case QMessageBox::Yes:
        break;
    case QMessageBox::No:
    default:
        ui->registrationButton->setEnabled(false);
        ui->namelineEdit->setEnabled(false);
        ui->usernamelineEdit->setEnabled(false);
        ui->passwordlineEdit->setEnabled(false);
        QTimer::singleShot(3000, this, SLOT(backToMain()));
        ui->label_4->setText("3秒后返回主界面...");
        break;
    }
}

void RegistrationWindow::backToMain()
{
    ui->registrationButton->setEnabled(true);
    ui->namelineEdit->setEnabled(true);
    ui->usernamelineEdit->setEnabled(true);
    ui->passwordlineEdit->setEnabled(true);
    ui->label_4->clear();
    this->hide();
    emit back();
}

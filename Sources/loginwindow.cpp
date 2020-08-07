/**************************************************************************
作者: wen
日期: 2020-08-05
描述: 读取指定路径下密码文本的账号和密码，没有则生成默认密码。登录失败3次后，程序退出。
**************************************************************************/

#include "./Headers/loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1050,800);
    this->setWindowTitle("欢迎使用本系统");

    count = 3;

    QFile file("D:/Qt/qtcode/0720/SupermarketManagement/Default.txt");
    bool is_ok = file.open(QIODevice::ReadOnly);
    if(!is_ok)
    {
        file.open(QIODevice::WriteOnly);
        file.write("root\n");
        file.write("123456");
        file.close();
    }

    //初始化employeelist，调用一次后employeelist就相当于employee.json文件
    //比如：先对employeelist进行增加或删除操作，再把employeelist写入文件中，就相当于对文件进行了改写的操作
    DataProcessing::parseJsonFile(this,"D:/Qt/qtcode/0720/SupermarketManagement/employee.json","employee",EmployeeType);
    DataProcessing::parseJsonFile(this,"D:/Qt/qtcode/0720/SupermarketManagement/purchase.json","purchase",PurchaseType);
    DataProcessing::parseJsonFile(this,"D:/Qt/qtcode/0720/SupermarketManagement/inventory.json","inventory",InventoryType);
    DataProcessing::parseJsonFile(this,"D:/Qt/qtcode/0720/SupermarketManagement/sales.json","sales",SalesType);
}

LoginWindow::~LoginWindow()
{
    qDebug() << "~LoginWindow()";
    delete ui;
}

void LoginWindow::on_pushButton_clicked()
{
    if(ui->usernamelineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"无法登录","请输入用户名", QMessageBox::Ok);
        return;
    }

    if(ui->passwordlineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"无法登录","请输入密码", QMessageBox::Ok);
        return;
    }

    //管理员登入，进入管理员界面
    if("root" == ui->usernamelineEdit->text() && "123456" == ui->passwordlineEdit->text())
    {
        admin = new AdministratorWindow(this);
        admin->show();
        this->hide();
    }
    else
    {
        for(int i = 0; i < DataProcessing::employeelist.size(); i++)
        {
            //员工登入，进入员工界面
            if(ui->usernamelineEdit->text() == DataProcessing::employeelist.at(i).getUsername()
                    && ui->passwordlineEdit->text() == DataProcessing::employeelist.at(i).getPassword())
            {
                staff = new StaffWindow(this);
                staff->show();
                this->hide();
                return;
            }
        }

        if(count > 1)
        {
            ui->passwordlineEdit->clear();
            QMessageBox::information(this,"登录错误",QString("您输入的用户名或密码有误，请重新输入。剩余输入次数：%1").arg(--count));
        }
        else
        {
            QMessageBox::information(this,"登录失败","您的账户不存在，请联系管理员进行解决\n"
                                                 "管理员联系方式：123456789");
            this->hide();
            qApp->exit();
        }
    }
}

/**************************************************************************
作者: wen
日期: 2020-08-05
描述: 显示广告界面，3s后跳转到登录界面
**************************************************************************/

#include "./Headers/supermarketmanagement.h"
#include "ui_supermarketmanagement.h"

SupermarketManagement::SupermarketManagement(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SupermarketManagement)
{
    ui->setupUi(this);
    this->setFixedSize(1050,800);
    this->setWindowTitle("超市管理系统");

    //TODO 将视频或者图片广告显示在控件上

    QTimer::singleShot(3000, this, SLOT(loginSystem()));
}

SupermarketManagement::~SupermarketManagement()
{
    qDebug() << "~SupermarketManagement()";
    delete ui;
}

void SupermarketManagement::loginSystem()
{
    login = new LoginWindow(this);
    login->show();
    this->hide();
}

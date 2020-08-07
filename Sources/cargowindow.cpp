/**************************************************************************
作者: wen
日期: 2020-08-05
描述: 上架指定的商品，前提是该商品存在于库存文本中，并且该商品的库存数量不为0。
      采购按键对应的界面也是这个界面，但是功能和上架不同。
**************************************************************************/

#include "./Headers/cargowindow.h"
#include "ui_cargowindow.h"
#include <QDebug>

CargoWindow::CargoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CargoWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1050,800);
}

CargoWindow::~CargoWindow()
{
    qDebug() << "~CargoWindow()";
    delete ui;
}

void CargoWindow::putButtonInit()
{
    QFont font;
    font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
    font.setPointSize(16);

    purchaseLabel = new QLabel(ui->layoutWidget_2);
    purchaseLabel->setObjectName(QString::fromUtf8("purchaseLabel"));
    purchaseLabel->setText("采购价：");
    purchaseLabel->setFont(font);
    ui->gridLayout->addWidget(purchaseLabel, 3, 0, 1, 1);

    purchaseLineEdit = new QLineEdit(ui->layoutWidget_2);
    purchaseLineEdit->setObjectName(QString::fromUtf8("purchaseLineEdit"));
    ui->gridLayout->addWidget(purchaseLineEdit, 3, 1, 1, 1);

    this->setWindowTitle("上架货物");
    ui->pushButton->setText("上架");
    connect(ui->pushButton,&QPushButton::clicked,this,&CargoWindow::putButton);
}

void CargoWindow::purchaseButtonInit()
{
    this->setWindowTitle("采购货物");
    ui->pushButton->setText("创建");
    connect(ui->pushButton,&QPushButton::clicked,this,&CargoWindow::purchaseButtonClicked);
}

void CargoWindow::putButton()
{
    if(ui->productNameEdit->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入商品名");
        return;
    }

    if(ui->amountLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入商品数量");
        return;
    }

    if(ui->priceLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入商品采购价");
        return;
    }

    if(0 >= ui->amountLineEdit->text().toInt())
    {
        QMessageBox::information(this,"提示","上架数量为大于0的整数");
        ui->amountLineEdit->clear();
        return;
    }

    if(0 >= ui->priceLineEdit->text().toDouble())
    {
        QMessageBox::information(this,"提示","售价应为大于0的整数");
        ui->priceLineEdit->clear();
        return;
    }

    if(purchaseLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入商品采购价");
        return;
    }

    QString name = ui->productNameEdit->text();
    double purchasePrice = purchaseLineEdit->text().toDouble();

    for(int i = 0; i < DataProcessing::inventorylist.size(); i++)
    {
        if(name == DataProcessing::inventorylist.at(i).getName()
                && purchasePrice - DataProcessing::inventorylist.at(i).getPurchasePrice() < 1e-10
                && purchasePrice - DataProcessing::inventorylist.at(i).getPurchasePrice() > -1e-10)
        {
            int amount = DataProcessing::inventorylist.at(i).getAmount();
            int salesAmount = ui->amountLineEdit->text().toInt();
            if(0 > amount-salesAmount)
            {
                QMessageBox::information(this,"上架失败","该种商品的库存数量不足，请重新输入数量");
                ui->amountLineEdit->clear();;
                return;
            }
            double shoppingPrice = DataProcessing::inventorylist.at(i).getShoppingPrice();

            DataProcessing::inventorylist.removeAt(i);
            DataProcessing::inventorylist.insert(i,Commodity(name,amount-salesAmount,purchasePrice,shoppingPrice));
            DataProcessing::generateJsonData(InventoryType);
            break;
        }
        else if(i == DataProcessing::inventorylist.size()-1)
        {
            QMessageBox::information(this,"上架失败","没有该种商品");
            ui->productNameEdit->clear();
            ui->amountLineEdit->clear();
            ui->priceLineEdit->clear();
            purchaseLineEdit->clear();
            return;
        }
    }
    DataProcessing::saleslist.insert(DataProcessing::saleslist.size(),
                    Commodity(name,ui->amountLineEdit->text().toInt(),purchaseLineEdit->text().toDouble(),
                              ui->priceLineEdit->text().toDouble()));
    DataProcessing::generateJsonData(SalesType);

    purchaseLineEdit->clear();
    ui->productNameEdit->clear();
    ui->amountLineEdit->clear();
    ui->priceLineEdit->clear();
    int ret = QMessageBox::information(this,"提示","操作成功,是否需要继续", QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);

    switch (ret)
    {
    case QMessageBox::Yes:
        break;
    case QMessageBox::No:
    default:
        emit back();
        this->hide();
        break;
    }
}

void CargoWindow::purchaseButtonClicked()
{
    if(ui->productNameEdit->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入商品名");
        return;
    }

    if(ui->amountLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入采购数量");
        return;
    }

    if(ui->priceLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入商品采购价");
        return;
    }

    if(0 >= ui->amountLineEdit->text().toInt())
    {
        QMessageBox::information(this,"提示","采购数量为大于0的整数");
        ui->amountLineEdit->clear();
        return;
    }

    if(0 >= ui->priceLineEdit->text().toDouble())
    {
        QMessageBox::information(this,"提示","采购价应为大于0的整数");
        ui->priceLineEdit->clear();
        return;
    }

    if(14 == DataProcessing::purchaselist.size())
    {
        QMessageBox::information(this,"无法创建","采购种类一次最多为14种，请先结算采购清单");
        return;
    }

    double purchasePrice = ui->priceLineEdit->text().toDouble();
    for(int i = 0; i < DataProcessing::purchaselist.size(); i++)
    {
        if(ui->productNameEdit->text() == DataProcessing::purchaselist.at(i).getName()
                && purchasePrice - DataProcessing::purchaselist.at(i).getPurchasePrice() < 1e-10
                && purchasePrice - DataProcessing::purchaselist.at(i).getPurchasePrice() > -1e-10)
        {
            QMessageBox::information(this,"无法创建","该种商品已经在采购清单上");
            ui->productNameEdit->clear();
            ui->amountLineEdit->clear();
            ui->priceLineEdit->clear();
            return;
        }
    }
    DataProcessing::purchaselist.insert(DataProcessing::purchaselist.size(),
                    Commodity(ui->productNameEdit->text(),ui->amountLineEdit->text().toInt(),ui->priceLineEdit->text().toDouble()));
    DataProcessing::generateJsonData(PurchaseType);

    ui->productNameEdit->clear();
    ui->amountLineEdit->clear();
    ui->priceLineEdit->clear();
    int ret = QMessageBox::information(this,"提示","操作成功,是否需要继续", QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);

    switch (ret)
    {
    case QMessageBox::Yes:
        break;
    case QMessageBox::No:
    default:
        emit back();
        this->hide();
        break;
    }
}

void CargoWindow::on_returnButton_clicked()
{
    emit back();
    this->hide();
}

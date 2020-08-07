/**************************************************************************
作者: wen
日期: 2020-08-05
描述: 货物管理界面。显示采购和销售文本。可以一键添加或添加指定的库存文本中拥有的货物到
     销售文本中，还可以下架选中的商品，并将数据重新写入库存文本和销售文本中。
**************************************************************************/

#include "./Headers/cargomanagementwindow.h"
#include "ui_cargomanagementwindow.h"
#include <QDebug>

CargoManagementWindow::CargoManagementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CargoManagementWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1050,800);
    this->setWindowTitle("货物管理");

    QStringList header;
    header << "商品名" << "数量" << "采购价";
    ui->purchaseTableWidget->setColumnCount(3);
    ui->purchaseTableWidget->setHorizontalHeaderLabels(header);
    ui->purchaseTableWidget->setFixedWidth(4*ui->purchaseTableWidget->width());
    ui->purchaseTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    header.clear();
    header << "商品名" << "数量" << "售价";
    ui->salesTableWidget->setColumnCount(3);
    ui->salesTableWidget->setHorizontalHeaderLabels(header);
    ui->salesTableWidget->setFixedWidth(4*ui->salesTableWidget->width());
    ui->salesTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->deleteButton->setEnabled(false);

    purchaseCargo = new CargoWindow(this);
    purchaseCargo->purchaseButtonInit();
    connect(purchaseCargo,&CargoWindow::back,this,&CargoManagementWindow::showMain);

    putCargo = new CargoWindow(this);
    putCargo->putButtonInit();
    connect(putCargo,&CargoWindow::back,this,&CargoManagementWindow::showMain);
}

CargoManagementWindow::~CargoManagementWindow()
{
    qDebug() << "~CargoManagementWindow()";
    delete ui;
}

void CargoManagementWindow::showMain()
{
    this->show();
}

void CargoManagementWindow::addPurchaseButton()
{
    ui->pushButton->setText("采购");
    ui->pushButton->setObjectName(QString::fromUtf8("purchaseBtn"));
    connect(ui->pushButton,&QPushButton::clicked,this,&CargoManagementWindow::purchaseButtonClicked);
}

void CargoManagementWindow::addPurchaseSettleButton()
{
    ui->pushButton->setText("结算");
    ui->pushButton->setObjectName(QString::fromUtf8("purchaseSettleBtn"));
    connect(ui->pushButton,&QPushButton::clicked,this,&CargoManagementWindow::purchaseSettleButtonClicked);
}

void CargoManagementWindow::on_returnpushButton_clicked()
{
    emit backToMain();
}

void CargoManagementWindow::on_updatepushButton_clicked()
{
    ui->purchaseTableWidget->setRowCount(DataProcessing::purchaselist.size());
    for(int i = 0; i < DataProcessing::purchaselist.size(); i++)
    {
        ui->purchaseTableWidget->setItem(i,0,new QTableWidgetItem(DataProcessing::purchaselist.at(i).getName()));
        QString amount = QString::number(DataProcessing::purchaselist.at(i).getAmount());
        ui->purchaseTableWidget->setItem(i,1,new QTableWidgetItem(amount));
        QString price = QString::number(DataProcessing::purchaselist.at(i).getPurchasePrice());
        ui->purchaseTableWidget->setItem(i,2,new QTableWidgetItem(price));
    }

    ui->salesTableWidget->setRowCount(DataProcessing::saleslist.size());
    for(int i = 0; i < DataProcessing::saleslist.size(); i++)
    {
        ui->salesTableWidget->setItem(i,0,new QTableWidgetItem(DataProcessing::saleslist.at(i).getName()));
        QString amount = QString::number(DataProcessing::saleslist.at(i).getAmount());
        ui->salesTableWidget->setItem(i,1,new QTableWidgetItem(amount));
        QString price = QString::number(DataProcessing::saleslist.at(i).getShoppingPrice());
        ui->salesTableWidget->setItem(i,2,new QTableWidgetItem(price));
    }
}

void CargoManagementWindow::on_addAllButton_clicked()
{
    if(0 == DataProcessing::inventorylist.size())
    {
        QMessageBox::information(this,"提示","库存为空，一键添加失败");
        return;
    }

    int count = 0;
    for(int i = 0; i < DataProcessing::inventorylist.size(); i++)
    {
        int amount = DataProcessing::inventorylist.at(i).getAmount();
        if(0==amount)
        {
            count++;
            continue;
        }
        QString name = DataProcessing::inventorylist.at(i).getName();
        double shoppingPrice = DataProcessing::inventorylist.at(i).getShoppingPrice();
        double purchasePrice = DataProcessing::inventorylist.at(i).getPurchasePrice();
        DataProcessing::saleslist.insert(DataProcessing::saleslist.size(),Commodity(name,amount,purchasePrice,shoppingPrice));

        DataProcessing::inventorylist.removeAt(i);
        DataProcessing::inventorylist.insert(i,Commodity(name,0,purchasePrice,shoppingPrice));
    }

    if(count == DataProcessing::inventorylist.size())
    {
        QMessageBox::information(this,"提示","库存中的所有商品都已上架，没有库存了");
        return;
    }

    DataProcessing::generateJsonData(SalesType);
    DataProcessing::generateJsonData(InventoryType);
    QMessageBox::information(this,"提示","一键添加成功");
}

void CargoManagementWindow::on_putButton_clicked()
{
    if(0 == DataProcessing::inventorylist.size())
    {
        QMessageBox::information(this,"提示","库存为空，上架失败");
        return;
    }

    int count = 0;
    for(int i=0; i<DataProcessing::inventorylist.size(); i++)
    {
        int amount = DataProcessing::inventorylist.at(i).getAmount();
        if(0==amount)
        {
            count++;
            continue;
        }
    }

    if(count == DataProcessing::inventorylist.size())
    {
        QMessageBox::information(this,"提示","库存中的所有商品都已上架");
        return;
    }

    putCargo->show();
    this->hide();
}

void CargoManagementWindow::on_deleteButton_clicked()
{
    int ret = QMessageBox::information(this,"提示","是否要下架该商品", QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(QMessageBox::No == ret)
    {
        return;
    }

    QTableWidgetItem *item = ui->salesTableWidget->currentItem();
    int row = item->row();
    QString name = DataProcessing::saleslist.at(row).getName();
    double purchasePrice = DataProcessing::saleslist.at(row).getPurchasePrice();

    int i;
    for(i = 0; i < DataProcessing::inventorylist.size(); i++)
    {
        //两个浮点数相差足够小，认为他们相同
        if(name == DataProcessing::inventorylist.at(i).getName()
                && purchasePrice - DataProcessing::inventorylist.at(i).getPurchasePrice() < 1e-10
                && purchasePrice - DataProcessing::inventorylist.at(i).getPurchasePrice() > -1e-10)
        {
            qDebug() << "void CargoManagementWindow::on_deleteButton_clicked()";
            int salesAmount = DataProcessing::saleslist.at(row).getAmount();
            int amount = DataProcessing::inventorylist.at(i).getAmount();
            double shoppingPrice = DataProcessing::inventorylist.at(i).getShoppingPrice();
            double purchasePrice = DataProcessing::inventorylist.at(i).getPurchasePrice();

            DataProcessing::inventorylist.removeAt(i);
            DataProcessing::inventorylist.insert(i,Commodity(name,amount+salesAmount,purchasePrice,shoppingPrice));
            break;
        }
    }

    //没在库存文本中找到相应的货物，则将选中的想要下架的商品直接添加进入库存文本中
    if(i == DataProcessing::inventorylist.size())
    {
        int salesAmount = DataProcessing::saleslist.at(row).getAmount();
        DataProcessing::inventorylist.insert(i,Commodity(name,salesAmount,purchasePrice));
    }

    DataProcessing::generateJsonData(InventoryType);

    DataProcessing::saleslist.removeAt(row);
    ui->salesTableWidget->removeRow(row);
    DataProcessing::generateJsonData(SalesType);
    ui->deleteButton->setEnabled(false);
    QMessageBox::information(this,"提示","下架成功");
}

void CargoManagementWindow::on_salesTableWidget_cellClicked()
{
    ui->deleteButton->setEnabled(true);
}

void CargoManagementWindow::on_purchaseTableWidget_cellClicked()
{
    ui->deleteButton->setEnabled(false);
}

void CargoManagementWindow::purchaseButtonClicked()
{
    purchaseCargo->show();
    this->hide();
}

void CargoManagementWindow::purchaseSettleButtonClicked()
{
    if(0 == DataProcessing::purchaselist.size())
    {
        QMessageBox::information(this,"提示","采购清单上没有未结算的货物");
        return;
    }

    double price = 0;
    for(int i = 0; i < DataProcessing::purchaselist.size(); i++)
    {
        price += DataProcessing::purchaselist.at(i).getPurchasePrice()*DataProcessing::purchaselist.at(i).getAmount();
    }

    QString information = QString("是否要结算采购?\n需要支付的采购金额为:%1RMB").arg(price);
    int ret = QMessageBox::information(this,"提示",information, QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);

    switch (ret)
    {
    case QMessageBox::Yes:
        for(int i = 0; i < DataProcessing::purchaselist.size(); i++)
        {
            QString name = DataProcessing::purchaselist.at(i).getName();
            int amount = DataProcessing::purchaselist.at(i).getAmount();
            double purchasePrice = DataProcessing::purchaselist.at(i).getPurchasePrice();

            int j;
            for(j = 0; j < DataProcessing::inventorylist.size(); j++)
            {
                if(name == DataProcessing::inventorylist.at(j).getName()
                        && purchasePrice-DataProcessing::inventorylist.at(j).getPurchasePrice() < 1e-10
                        && purchasePrice-DataProcessing::inventorylist.at(j).getPurchasePrice() > -1e-10)
                {
                    qDebug() << "void StaffWindow::purchaseSettlement()";
                    break;
                }
            }

            if(j < DataProcessing::inventorylist.size())
            {
                int inventoryAmount = DataProcessing::inventorylist.at(j).getAmount();
                double shoppingPrice = DataProcessing::inventorylist.at(j).getShoppingPrice();
                DataProcessing::inventorylist.removeAt(j);
                DataProcessing::inventorylist.insert(j,Commodity(name,inventoryAmount+amount,purchasePrice,shoppingPrice));
            }
            else
            {
                double shoppingPrice = DataProcessing::purchaselist.at(i).getShoppingPrice();
                DataProcessing::inventorylist.insert(DataProcessing::inventorylist.size(),Commodity(name,amount,purchasePrice,shoppingPrice));
            }
        }
        DataProcessing::purchaselist.clear();
        DataProcessing::generateJsonData(PurchaseType);
        DataProcessing::generateJsonData(InventoryType);
        QMessageBox::information(this,"提示","结算成功");
        [[clang::fallthrough]];
    case QMessageBox::No:
    default:
        break;
    }
}

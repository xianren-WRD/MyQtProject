/**************************************************************************
作者: wen
日期: 2020-08-05
描述: 选择商品后，可以输入商品的数量进行选择购买，并将选择的记录显示在控件上。结算后
      将销售记录写入销售历史记录文本中。
**************************************************************************/

#include "./Headers/shoppingwindow.h"
#include "ui_shoppingwindow.h"
#include <QDebug>

ShoppingWindow::ShoppingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShoppingWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1050,800);
    this->setWindowTitle("购物");

    historyAmount = 0;
    totalAmount = 0;

    QStringList header;
    header << "商品名" << "数量" << "售价";
    ui->salesTableWidget->setColumnCount(3);
    ui->salesTableWidget->setHorizontalHeaderLabels(header);
    ui->salesTableWidget->setFixedWidth(4*ui->salesTableWidget->width());
    ui->salesTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    header.clear();
    header << "商品名" << "数量" << "总价";
    ui->historyTableWidget->setColumnCount(3);
    ui->historyTableWidget->setHorizontalHeaderLabels(header);
    ui->historyTableWidget->setFixedWidth(4*ui->historyTableWidget->width());
    ui->historyTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->selectButton->setEnabled(false);
    ui->amountLineEdit->setEnabled(false);
}

ShoppingWindow::~ShoppingWindow()
{
    delete ui;
}

void ShoppingWindow::on_returnButton_clicked()
{
    emit back();
}

void ShoppingWindow::on_selectButton_clicked()
{
    int shoppingAmount = ui->amountLineEdit->text().toInt();
    if(0 >= shoppingAmount)
    {
        QMessageBox::information(this,"提示","购买数量应该大于0");
        ui->amountLineEdit->clear();
        return;
    }

    QTableWidgetItem *item = ui->salesTableWidget->currentItem();
    int row = item->row();

    int amount = DataProcessing::saleslist.at(row).getAmount();
    if(0 > amount-shoppingAmount)
    {
        QMessageBox::information(this,"提示","购买数量不能大于销售数量");
        ui->amountLineEdit->clear();
        return;
    }

    QString name = DataProcessing::saleslist.at(row).getName();
    double shoppingPrice = DataProcessing::saleslist.at(row).getShoppingPrice();
    double purchasePrice = DataProcessing::saleslist.at(row).getPurchasePrice();

    DataProcessing::saleslist.removeAt(row);
    DataProcessing::saleslist.insert(row,Commodity(name,amount-shoppingAmount,purchasePrice,shoppingPrice));
    DataProcessing::generateJsonData(SalesType);

    ui->historyTableWidget->setRowCount(historyAmount+1);
    ui->historyTableWidget->setItem(historyAmount,0,new QTableWidgetItem(name));
    ui->historyTableWidget->setItem(historyAmount,1,new QTableWidgetItem(QString::number(shoppingAmount)));
    double price = shoppingAmount*shoppingPrice;
    ui->historyTableWidget->setItem(historyAmount,2,new QTableWidgetItem(QString::number(price)));

    historyAmount++;
    totalAmount += price;
    ui->selectButton->setEnabled(false);
    ui->amountLineEdit->clear();
    ui->amountLineEdit->setEnabled(false);

    //选择完商品后，刷新一次，将售价为0的商品清理掉
    on_updateButton_clicked();
}

void ShoppingWindow::on_settlementButton_clicked()
{
    if(0 == historyAmount)
    {
        QMessageBox::information(this,"提示","购买车为空，请购买商品后再结算");
        return;
    }

    QString information = QString("是否要结算?\n需要支付的总金额为:%1RMB").arg(totalAmount);
    int ret = QMessageBox::information(this,"提示",information, QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(QMessageBox::No == ret)
    {
        return;
    }

    //将购买的记录写入销售记录文本中
    QJsonObject typeObj;
    QJsonArray array;
    QString filename = "salehistory";

    for(int i=0; i<historyAmount;i++)
    {
        typeObj.insert("name",ui->historyTableWidget->item(i,0)->text());
        typeObj.insert("amount",ui->historyTableWidget->item(i,1)->text().toInt());
        typeObj.insert("sales",ui->historyTableWidget->item(i,2)->text().toDouble());
        typeObj.insert("time",QDateTime::currentDateTime().toString());
        array.append(typeObj);
    }

    QJsonObject obj;
    obj.insert(filename,array);

    QJsonDocument document;
    document.setObject(obj);

    QByteArray jsonData = document.toJson();

    QFile file(QString("D:/Qt/qtcode/0720/SupermarketManagement/%1.json").arg(filename));
    file.open(QIODevice::WriteOnly);
    file.write(jsonData);
    file.close();

    ui->historyTableWidget->clear();
    historyAmount = 0;
    totalAmount = 0;
    QMessageBox::information(this,"提示","结算成功");
}

void ShoppingWindow::on_salesTableWidget_cellClicked()
{
    ui->selectButton->setEnabled(true);
    ui->amountLineEdit->setEnabled(true);
}

void ShoppingWindow::on_historyTableWidget_cellClicked()
{
    ui->selectButton->setEnabled(false);
    ui->amountLineEdit->setEnabled(false);
}

void ShoppingWindow::on_updateButton_clicked()
{
    for(int i = 0; i < DataProcessing::saleslist.size(); i++)
    {
        if(0 == DataProcessing::saleslist.at(i).getAmount())
        {
            DataProcessing::saleslist.removeAt(i);
            DataProcessing::generateJsonData(SalesType);
        }
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

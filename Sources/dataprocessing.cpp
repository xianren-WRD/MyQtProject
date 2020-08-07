/**************************************************************************
作者: wen
日期: 2020-08-05
描述: 根据不同类型的参数生成不同格式的json数据写入到文本中。将指定json文件按照参数给定
      的格式解析出来，将得到的对象存放在对应的QList中。
**************************************************************************/

#include "./Headers/dataprocessing.h"
#include <QDebug>

QList<Employee>  DataProcessing::employeelist = QList<Employee>();
QList<Commodity>  DataProcessing::purchaselist = QList<Commodity>();
QList<Commodity>  DataProcessing::inventorylist = QList<Commodity>();
QList<Commodity>  DataProcessing::saleslist = QList<Commodity>();

DataProcessing::DataProcessing()
{

}

DataProcessing::~DataProcessing()
{

}

void DataProcessing::generateJsonData(DataType type)
{
    QJsonObject typeObj;
    QJsonArray array;
    QString filename;

    switch (type)
    {
    case EmployeeType:
        for(int i = 0; i < employeelist.size(); i++)
        {
            typeObj.insert("name",employeelist.at(i).getName());
            typeObj.insert("username",employeelist.at(i).getUsername());
            typeObj.insert("password",employeelist.at(i).getPassword());
            array.append(typeObj);
        }
        filename = "employee";
        break;
    case PurchaseType:
        for(int i = 0; i < purchaselist.size(); i++)
        {
            typeObj.insert("name",purchaselist.at(i).getName());
            typeObj.insert("amount",purchaselist.at(i).getAmount());
            typeObj.insert("purchaseprice",purchaselist.at(i).getPurchasePrice());
            array.append(typeObj);
        }
        filename = "purchase";
        break;
    case InventoryType:
        for(int i = 0; i < inventorylist.size(); i++)
        {
            typeObj.insert("name",inventorylist.at(i).getName());
            typeObj.insert("amount",inventorylist.at(i).getAmount());
            typeObj.insert("purchaseprice",inventorylist.at(i).getPurchasePrice());
            typeObj.insert("shoppingprice",inventorylist.at(i).getShoppingPrice());
            array.append(typeObj);
        }
        filename = "inventory";
        break;
    case SalesType:
        for(int i = 0; i < saleslist.size(); i++)
        {
            typeObj.insert("name",saleslist.at(i).getName());
            typeObj.insert("amount",saleslist.at(i).getAmount());
            typeObj.insert("purchaseprice",saleslist.at(i).getPurchasePrice());
            typeObj.insert("shoppingprice",saleslist.at(i).getShoppingPrice());
            array.append(typeObj);
        }
        filename = "sales";
        break;
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
}

void DataProcessing::parseJsonFile(QWidget *parent,const QString &filepath,const QString &filename,DataType type)
{
    QByteArray data;
    QFile file(filepath);  
    bool is_ok = file.open(QIODevice::ReadOnly); 
    if(is_ok)
    {
         data = file.readAll();
    }
    else
    {
        QMessageBox::information(parent,"出错提示",QString("%1.json文件打开失败").arg(filename));
        return;
    }

    QJsonDocument document =  QJsonDocument::fromJson(data);
    QJsonObject object = document.object();
    QJsonArray array = object.value(filename).toArray();

    switch (type)
    {
    case EmployeeType:
        for(int i=0; i<array.size(); i++)
        {
            QJsonObject employee = array.at(i).toObject();
            QString name = employee.value("name").toString();
            QString username = employee.value("username").toString();
            QString password = employee.value("password").toString();

            Employee obj(name,username,password);
            employeelist.append(obj);  //使用append，如果多次调用会出现重复的内容。可以用insert
        }
        break;
    case PurchaseType:
        for(int i=0; i<array.size(); i++)
        {
            QJsonObject commodity = array.at(i).toObject();
            QString name = commodity.value("name").toString();
            int amount = commodity.value("amount").toInt();
            double purchasePrice = commodity.value("purchaseprice").toDouble();

            Commodity obj(name,amount,purchasePrice);
            purchaselist.append(obj);
        }
        break;
    case InventoryType:
        for(int i=0; i<array.size(); i++)
        {
            QJsonObject commodity = array.at(i).toObject();
            QString name = commodity.value("name").toString();
            int amount = commodity.value("amount").toInt();
            double purchasePrice = commodity.value("purchaseprice").toDouble();
            double shippingPrice = commodity.value("shoppingprice").toDouble();

            Commodity obj(name,amount,purchasePrice,shippingPrice);
            inventorylist.append(obj);
        }
        break;
    case SalesType:
        for(int i=0; i<array.size(); i++)
        {
            QJsonObject commodity = array.at(i).toObject();
            QString name = commodity.value("name").toString();
            int amount = commodity.value("amount").toInt();
            double purchasePrice = commodity.value("purchaseprice").toDouble();
            double shippingPrice = commodity.value("shoppingprice").toDouble();

            Commodity obj(name,amount,purchasePrice,shippingPrice);
            saleslist.append(obj);
        }
        break;
    }
    file.close();
}

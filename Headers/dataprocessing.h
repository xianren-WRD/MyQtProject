#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include "commodity.h"
#include "employee.h"

enum DataType
{
    EmployeeType = 0,
    PurchaseType = 1,
    InventoryType = 2,
    SalesType = 3
};

class DataProcessing
{
public:
    DataProcessing();
    ~DataProcessing();

    /*
    *功能: 生成json数据，并将数据写入不同的指定的文本中
    *参数:
    *     type: 表明生成的json的格式以及类型，并最终写入对应的文本中
    */
    static void generateJsonData(DataType type);

    /*
    *功能: 解析json文件，将得到的数据存放在对应的列表中。
    *参数:
    *     parent: 为消息盒子指定父控件
    *     filepath: 要解析的文件所在的绝对路径
    *     filename: 要解析的文件的对象名
    *     type: 表明要将json以什么样的格式以及类型解析
    * 注意: 初始化调用一次即可
    */
    static void parseJsonFile(QWidget *parent,const QString &filepath,const QString &filename,DataType type);

    static QList<Employee> employeelist;
    static QList<Commodity> purchaselist;
    static QList<Commodity> inventorylist;
    static QList<Commodity> saleslist;
};

#endif // DATAPROCESSING_H

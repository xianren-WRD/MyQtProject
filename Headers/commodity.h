#ifndef COMMODITY_H
#define COMMODITY_H

#include <QString>

//商品类 -- 相关set方法没有用到，因为使用的QList的at方法返回的是const对象
//说明：商品名相同，但是采购价不同，也属于不同的商品。商品名和采购价都相同，才算相同的商品。
class Commodity
{
public:
    Commodity(QString name,int amount,double purchasePrice);
    Commodity(QString name,double shippingPrice,int amount);
    Commodity(QString name,int amount,double purchasePrice,double shippingPrice);
    QString getName() const;
    void setName(const QString &value);

    int getAmount() const;
    void setAmount(int value);


    double getPurchasePrice() const;
    void setPurchasePrice(double value);

    double getShoppingPrice() const;
    void setShoppingPrice(double value);

private:
    QString name;
    int amount;
    double purchasePrice;
    double shoppingPrice;
    //可以计算出商品的默认售价，一键添加货物的时候会用到
    static double grossMargin;//毛利率
};

#endif // COMMODITY_H

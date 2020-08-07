/**************************************************************************
作者: wen
日期: 2020-08-05
**************************************************************************/

#include "./Headers/commodity.h"

double Commodity::grossMargin = 0.2;

Commodity::Commodity(QString name, int amount, double purchasePrice)
            :name(name),amount(amount),purchasePrice(purchasePrice)
{
    shoppingPrice = purchasePrice/(1-grossMargin);
}

Commodity::Commodity(QString name, double shoppingPrice, int amount)
            :name(name),amount(amount),shoppingPrice(shoppingPrice)
{

}

Commodity::Commodity(QString name, int amount, double purchasePrice, double shoppingPrice)
            :name(name),amount(amount),purchasePrice(purchasePrice),shoppingPrice(shoppingPrice)
{

}

QString Commodity::getName() const
{
    return name;
}

void Commodity::setName(const QString &value)
{
    name = value;
}

int Commodity::getAmount() const
{
    return amount;
}

void Commodity::setAmount(int value)
{
    amount = value;
}

double Commodity::getPurchasePrice() const
{
    return purchasePrice;
}

void Commodity::setPurchasePrice(double value)
{
    purchasePrice = value;
}

double Commodity::getShoppingPrice() const
{
    return shoppingPrice;
}

void Commodity::setShoppingPrice(double value)
{
    shoppingPrice = value;
}

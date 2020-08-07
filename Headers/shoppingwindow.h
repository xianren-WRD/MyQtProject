#ifndef SHOPPINGWINDOW_H
#define SHOPPINGWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "dataprocessing.h"

namespace Ui {
class ShoppingWindow;
}

class ShoppingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShoppingWindow(QWidget *parent = nullptr);
    ~ShoppingWindow();

private slots:
    void on_returnButton_clicked();

    //TODO 如果没有结算就关闭窗口会导致一部分的商品丢失，可以重写QEvent解决，当窗口关闭的时候提示用户还有未结算的货物
    //如果不结算的话，则保存在一个文本里面，下次程序启动读取文本的内容，这样可以避免丢失数据
    void on_selectButton_clicked();

    void on_settlementButton_clicked();

    void on_salesTableWidget_cellClicked();

    void on_historyTableWidget_cellClicked();

    void on_updateButton_clicked();

signals:
    void back();

private:
    Ui::ShoppingWindow *ui;
    int historyAmount;//购买商品的记录的条数
    double totalAmount;//总的购买金额
};

#endif // SHOPPINGWINDOW_H

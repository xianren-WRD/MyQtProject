#ifndef SUPERMARKETMANAGEMENT_H
#define SUPERMARKETMANAGEMENT_H

#include <QMainWindow>
#include <QTimer>
#include "loginwindow.h"

namespace Ui {
class SupermarketManagement;
}

class SupermarketManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit SupermarketManagement(QWidget *parent = nullptr);
    ~SupermarketManagement();

private slots:
    void loginSystem();

private:
    Ui::SupermarketManagement *ui;
    LoginWindow *login;
};

#endif // SUPERMARKETMANAGEMENT_H

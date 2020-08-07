#ifndef CARGOWINDOW_H
#define CARGOWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include "dataprocessing.h"

namespace Ui {
class CargoWindow;
}

class CargoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CargoWindow(QWidget *parent = nullptr);
    ~CargoWindow();

public slots:
    void putButtonInit();

    void purchaseButtonInit();

private slots:
    void putButton();

    void purchaseButtonClicked();

    void on_returnButton_clicked();

signals:
    void back();

private:
    Ui::CargoWindow *ui;
    QLabel *purchaseLabel;
    QLineEdit *purchaseLineEdit;
};

#endif // CARGOWINDOW_H

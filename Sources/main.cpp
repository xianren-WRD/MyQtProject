/**************************************************************************
作者: wen
日期: 2020-08-05
**************************************************************************/

#include "./Headers/supermarketmanagement.h"
#include <QApplication>
#include <QFile>
#include <QLatin1String>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/res/qss/firstqss.qss");
    file.open(QFile::ReadOnly);
    QString css = QLatin1String(file.readAll());
    qApp->setStyleSheet(css);

    SupermarketManagement w;
    w.show();

    return a.exec();
}

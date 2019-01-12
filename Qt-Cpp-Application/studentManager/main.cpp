#include "addstu.h"
#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //addStu w;
    //w.show();
    MainWindow w;
    w.show();

//打开数据库连接
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("localhost");
    dataBase.setUserName("root");
    dataBase.setPassword("fmw19990718");
    dataBase.setDatabaseName("student");
    dataBase.open();
    bool ok=dataBase.open();
    if(ok)
    {
      qDebug()<<"open database success";
    }
    else
    {
      qDebug()<<"error open database";
    }


    return a.exec();
}

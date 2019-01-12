#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addstu.h"
#include "querystu.h"
#include <QSqlDatabase>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionaddStu_triggered()
{
    addStu a;
//    a.show();
    a.exec();   //模态视图

    //1. exec();
    //2. show();
}

void MainWindow::on_actionqueryStu_triggered()
{
    querystu q;
    q.exec();
}

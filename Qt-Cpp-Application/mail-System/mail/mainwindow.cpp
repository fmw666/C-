#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->userPass->setEchoMode(QLineEdit::Password);

 /*   connect(ui->lineEdit,
            SIGNAL(),
            this,
            SLOT()
                );    */
//    connect(ui->login_btn,SIGNAL(clicked()),this,SLOT(on_login_btn_clicked(bool checked)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_4_triggered()
{
    exit(1);
}

void MainWindow::on_action_triggered()
{
    QMessageBox::about(this,tr("成员"),tr("组长：陈关吉\n组员：范茂伟、欧云龙、李璐、李岩\t"));
}

void MainWindow::on_action_2_triggered()
{
    QMessageBox::about(this,tr("请添加我qq"),tr("QQ784958034    "));
}

void MainWindow::on_login_btn_clicked(bool checked)
{
    if(this->ui->userID->text().trimmed() == tr("admin") &&
          this->ui->userPass->text().trimmed()== tr("admin"))
    {
        QMessageBox::about(this,tr("提示"),tr("\n  登录成功！\t\n"));
        this->hide();
        emit showmain();
    }
    else
    {
        //用户输入存在错误
        QMessageBox::warning(this,tr("警告"),tr("\n请输入正确的账户和密码\t"),QMessageBox::tr("确定"));
        ui->userID->clear();  //清空姓名nameLine
        ui->userPass->clear();  //清空密码passwardLine
        ui->userID->setFocus();  //将鼠标重新定位到nameLine
    }

}


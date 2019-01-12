#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::receivelogin()
{
    this->show();
}

void login::getlogin3()
{
    this->show();
}

void login::retlogin()
{
    this->show();
}

void login::on_pushButton_clicked()
{
    this->hide();
    emit showmain1();
}

void login::on_pushButton_2_clicked()
{
    QMessageBox::information(this,tr("提示"),tr("\n确定进入服务端？\t"),QMessageBox::tr("确定"));
    this->hide();
    emit showmain2();
}

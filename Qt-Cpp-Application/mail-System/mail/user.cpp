#include "user.h"
#include "ui_user.h"
#include <QMessageBox>

User::User(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);

 //   connect(ui->send_btn,SIGNAL(clicked()),this,SLOT(clearContent()));

}

User::~User()
{
    delete ui;
}

void User::getlogin()
{
    this->show();
}

void User::on_send_btn_clicked()
{
    if(this->ui->IP->text().trimmed() == tr("127.0.0.1"))
    {
        QMessageBox::about(this,tr("发送状态"),tr("发送成功\t"));
        ui->content->setText("");
    }
    else
    {
        QMessageBox::warning(this,tr("警告"),tr("\n请输入正确的ip\t"),QMessageBox::tr("确定"));
        ui->IP->clear();  //清空姓名nameLine
        ui->IP->setFocus();  //将鼠标重新定位到nameLine
    }
}

void User::on_pushButton_clicked()
{
    this->hide();
    emit showmain2();
}

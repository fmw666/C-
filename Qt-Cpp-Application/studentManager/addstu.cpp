#include "addstu.h"
#include "ui_addstu.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QList>
#include <QButtonGroup>
#include <QAbstractButton>
#include <QCheckBox>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>

addStu::addStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStu)
{
    ui->setupUi(this);
}

addStu::~addStu()
{
    delete ui;
}

void addStu::on_btn_ok_clicked()
{
    QString name = this->ui->le_name->text();
    QString id = this->ui->le_id->text();
    QString sex = this->ui->sexGroup->checkedButton()->text();
    QList<QAbstractButton *> ins_list = this->ui->insGroup->buttons();
    QString ins;
    int i = 0;
    for(i = 0 ; i < ins_list.length();i++){
        QAbstractButton * che = ins_list.at(i);
        if(che->isChecked()){
            ins += che->text() + " ";
        }
    }
    QString age = this->ui->cbb_age->currentText();
    QString dev = this->ui->cbb_yx->currentText();

/*
    QMessageBox msgBox;

    msgBox.setText("请确认信息");
    msgBox.setInformativeText(name+'\n'+id);

//    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
//    msgBox.setDefaultButton(QMessageBox::Save);

    msgBox.addButton("确定",QMessageBox::AcceptRole);
    QPushButton * cbtn = msgBox.addButton("取消",QMessageBox::RejectRole);
    msgBox.setDefaultButton(cbtn);

    int ret = msgBox.exec();
*/
    //QMessageBox::aboutQt(this,"鸣谢");

    QString content = name + '\n' + id + '\n' + sex + '\n' + age + '\n' + dev + '\n' + ins;
    QString cnt = name + " " + id + " " + sex + " " + age + " " + dev + " " + ins + '\n';

    if(name.length() < 1 || id.length() < 1 || ins.length() < 1){
        QMessageBox::critical(this,"错误","信息填写不完整，请重新检查","确定");
    }else{
        int ret = QMessageBox::question(this,"请确认信息",content,"确认","取消");
        if(ret == 0){
            clearUserInterface();
            writeToFile(cnt);

            QSqlDatabase dataBase;
            QSqlQuery query(dataBase);

            query.exec("insert into student.information(name,id,sex,age,dev,ins) values('ABC',40,'男',18,'ss','as')");

            /*QString sql=QString("select *from information");
            query.exec(sql);

            QString savesql = QString("INSERT INTO information(name,id,sex,age,dev,ins)");
            savesql += QString(" VALUES('%1','%2','%3','%4','%5','%6')").arg(name).arg(id).arg(sex).arg(age).arg(dev).arg(ins);
            bool ok = query.exec(savesql);
            if(ok){
                  QMessageBox::about(NULL, "Save", "save new database success");
            }
            else{
                   QMessageBox::about(NULL, "Save", "error save new database");
            }*/

/*
            query.prepare("INSERT INTO STUDENT(name,id,sex,age,dev,ins)" "VALUES(:name,:id,:sex,:age,:dev,:ins)");
            query.bindValue(":name",name);
            query.bindValue(":id",id);
            query.bindValue(":sex",sex);
            query.bindValue(":age",age);
            query.bindValue(":dev",dev);
            query.bindValue(":ins",ins);
            query.exec();*/
        }
    }

}

void addStu::clearUserInterface()
{
    this->ui->le_name->clear();
    this->ui->le_id->clear();
    this->ui->rbtn_male->setChecked(true);
    this->ui->cbb_age->setCurrentIndex(0);
    this->ui->cbb_yx->setCurrentIndex(0);
    QList<QAbstractButton *> ins_list = this->ui->insGroup->buttons();
    int i = 0;
    for(i = 0;i < ins_list.length();i++){
        QAbstractButton *box = ins_list.at(i);
        box->setChecked(false);
    }
    this->ui->le_name->setFocus();
}

void addStu::writeToFile(QString cnt)
{
    QFile file("stu.txt");
    if(!file.open(QIODevice::Append | QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有保存！","确定");
        return;
    }
    QTextStream out(&file);
    out << cnt;
    file.close();
}

void addStu::on_btn_cancel_clicked()
{
    this->close();
}

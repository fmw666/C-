#include "showmail.h"
#include "ui_showmail.h"

showMail::showMail(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::showMail)
{
    ui->setupUi(this);
}

showMail::~showMail()
{
    delete ui;
}

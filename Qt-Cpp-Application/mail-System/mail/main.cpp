#include "mainwindow.h"
#include "user.h"
#include "login.h"
#include "../server/server.h"
#include "../Client/client.h"
#include <QApplication>
#include <QTcpSocket>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedHeight(350);
    w.setFixedWidth(430);
    w.setGeometry(800,400,400,600);
    w.setWindowTitle("Welcome");
    w.show();
    User l;
    l.setFixedHeight(350);
    l.setFixedWidth(430);
    l.setGeometry(800,400,400,600);
    l.setWindowTitle("写邮件");
    login i;
    i.setFixedHeight(250);
    i.setFixedWidth(430);
    i.setGeometry(800,400,0,0);
    i.setWindowTitle("主界面");
    server s;
    s.setFixedHeight(400);
    s.setFixedWidth(600);
    s.setGeometry(750,400,400,600);
    s.setWindowTitle("Server");
    client c;
    c.setFixedHeight(400);
    c.setFixedWidth(600);
    c.setGeometry(750,400,400,600);
    c.setWindowTitle("Client");
    QObject::connect(&w,SIGNAL(showmain()),&i,SLOT(receivelogin()));
    QObject::connect(&i,SIGNAL(showmain1()),&c,SLOT(getlogin()));
    QObject::connect(&c,SIGNAL(showmain()),&i,SLOT(retlogin()));
    QObject::connect(&i,SIGNAL(showmain2()),&s,SLOT(getlogin2()));
    QObject::connect(&c,SIGNAL(showmain()),&i,SLOT(retlogin()));

    return a.exec();
}

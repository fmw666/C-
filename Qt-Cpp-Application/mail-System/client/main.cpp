#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client w;
    w.setFixedHeight(400);
    w.setFixedWidth(600);
    w.setGeometry(800,400,400,600);
    w.setWindowTitle("Client");
    w.show();

    return a.exec();
}

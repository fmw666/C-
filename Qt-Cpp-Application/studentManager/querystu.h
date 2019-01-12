#ifndef QUERYSTU_H
#define QUERYSTU_H

#include <QDialog>
#include <QFile>
#include <QList>
#include <QString>
#include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {
class querystu;
}

class querystu : public QDialog
{
    Q_OBJECT

public:
    explicit querystu(QWidget *parent = 0);
    ~querystu();
    int readFromFile();
    void doQuery(int index,QString cnt);
    void disPlay(int row,QStringList subs);

private slots:
    void on_bt_search_clicked();

private:
    Ui::querystu *ui;
    QList<QString> stu_lines;
    QStandardItemModel * model;
};

#endif // QUERYSTU_H

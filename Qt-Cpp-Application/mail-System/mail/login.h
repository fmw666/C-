#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void receivelogin();

    void getlogin3();

    void retlogin();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::login *ui;

signals:
    void showmain1();
    void showmain2();
};

#endif // LOGIN_H


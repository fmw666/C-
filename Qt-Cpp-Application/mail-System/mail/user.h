#ifndef USER_H
#define USER_H

#include <QDialog>

namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = 0);
    ~User();

private slots:
   void getlogin();

   void on_send_btn_clicked();

   void on_pushButton_clicked();

signals:
    void showmain2();

public slots:


private:
    Ui::User *ui;
};

#endif // USER_H

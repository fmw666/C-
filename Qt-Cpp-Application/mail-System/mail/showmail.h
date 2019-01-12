#ifndef SHOWMAIL_H
#define SHOWMAIL_H

#include <QMainWindow>

namespace Ui {
class showMail;
}

class showMail : public QMainWindow
{
    Q_OBJECT

public:
    explicit showMail(QWidget *parent = 0);
    ~showMail();

private:
    Ui::showMail *ui;
};

#endif // SHOWMAIL_H

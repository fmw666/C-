#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_4_triggered();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_login_btn_clicked(bool checked);


signals:
    void showmain();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

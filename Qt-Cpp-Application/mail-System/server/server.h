#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QFile>
#include <QDateTime>


namespace Ui {
class server;
}

class server : public QMainWindow
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = 0);
    ~server();

    QTcpServer *server1;
    QTcpSocket *socket;
    QTcpServer *fileserver;
    QTcpSocket *filesocket;

private slots:
    void sendMessage();
    void acceptConnection();
    //接收客户端发送的数据
    void receiveData();

    void acceptFileConnection();
    void updateFileProgress();
    void displayError(QAbstractSocket::SocketError socketError);

    //选择发送的文件
    void selectFile();
    void sendFile();
    //更新文件传送进度
    void updateFileProgress(qint64);

    void getlogin2();

    void on_pushButton_clicked();

//    void on_pushButton_close_clicked();

private:
    Ui::server *ui;

    //传送文件相关变量
    qint64 totalBytes;
    qint64 bytesReceived;
    qint64 bytestoWrite;
    qint64 bytesWritten;
    qint64 filenameSize;
    QString filename;
    //每次发送数据大小
    qint64 perDataSize;
    QFile *localFile;
    //本地缓冲区
    QByteArray inBlock;
    QByteArray outBlock;

    //系统时间
    QDateTime current_date_time;
    QString str_date_time;
};

#endif // SERVER_H

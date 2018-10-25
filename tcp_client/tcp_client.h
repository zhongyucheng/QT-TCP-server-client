#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
namespace Ui {
class tcp_Client;
}

class tcp_Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit tcp_Client(QWidget *parent = 0);
    ~tcp_Client();

private slots:
    void on_btnConnect_clicked();

    void ReadData();
    void ReadError(QAbstractSocket::SocketError);

    void on_btnClear_clicked();

    void on_btnSend_clicked();


private:
    Ui::tcp_Client *ui;

    QTcpSocket *tcpClient;
    void Initialize();

};

#endif // TCP_CLIENT_H


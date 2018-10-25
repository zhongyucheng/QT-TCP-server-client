#ifndef SERVERMAIN_H
#define SERVERMAIN_H

#include <QWidget>
#include "mytcpserver.h"
namespace Ui {
class ServerMain;
}

class ServerMain : public QWidget
{
    Q_OBJECT

public:
    explicit ServerMain(QWidget *parent = 0);
    ~ServerMain();

private slots:

    void ClientReadData(int clientID,QString IP,int Port,QByteArray data);
    void ClientConnect(int clientID,QString IP,int Port);
    void ClientDisConnect(int clientID,QString IP,int Port);
    void on_btnListen_clicked();

    void on_btnSend_clicked();

    void on_btnClear_clicked();


private:
    Ui::ServerMain *ui;

    myTcpServer *server;

    void Initialize();
};

#endif // SERVERMAIN_H

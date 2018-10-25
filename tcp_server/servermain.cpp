#include "servermain.h"
#include "ui_servermain.h"
#include <QDebug>

ServerMain::ServerMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerMain)
{
    ui->setupUi(this);

    this->Initialize();
}

ServerMain::~ServerMain()
{
    delete ui;
}

void ServerMain::Initialize()
{
    ui->btnSend->setEnabled(false);
    ui->txtReceive->setReadOnly(true);
    server=new myTcpServer(this);
    connect(server,SIGNAL(ClientConnect(int,QString,int)),this,SLOT(ClientConnect(int,QString,int)));
    connect(server,SIGNAL(ClientDisConnect(int,QString,int)),this,SLOT(ClientDisConnect(int,QString,int)));
    connect(server,SIGNAL(ClientReadData(int,QString,int,QByteArray)),this,SLOT(ClientReadData(int,QString,int,QByteArray)));
}


void ServerMain::ClientReadData(int clientID,QString IP,int Port,QByteArray data)
{
    if (!data.isEmpty())
    {

            ui->txtReceive->append(tr("接收数据:%1 来自:[clientID:%2 IP:%3 Port:%4]")
                                   .arg(QString(data)).arg(clientID).arg(IP).arg(Port));

    }
}

void ServerMain::ClientConnect(int clientID,QString IP,int Port)
{
    ui->txtReceive->append(tr("客户端:[clientID:%1 IP:%2 Port:%3]上线")
                           .arg(clientID).arg(IP).arg(Port));
    ui->cboxClient->addItem(tr("%1:%2:%3").arg(clientID).arg(IP).arg(Port));
}

void ServerMain::ClientDisConnect(int clientID,QString IP,int Port)
{
    ui->txtReceive->append(tr("客户端:[clientID:%1 IP:%2 Port:%3]下线")
                           .arg(clientID).arg(IP).arg(Port));
    ui->cboxClient->removeItem(ui->cboxClient->findText(tr("%1:%2:%3").arg(clientID).arg(IP).arg(Port)));
}

void ServerMain::on_btnListen_clicked()
{
    if (ui->btnListen->text()=="监听")
    {
        bool ok=server->listen(QHostAddress::Any,ui->txtPort->text().toInt());
        if (ok)
        {
            ui->btnListen->setText("停止");
            ui->txtReceive->append("监听成功");
            ui->btnSend->setEnabled(true);
        }
    }
    else
    {
        server->close();
        ui->btnListen->setText("监听");
        ui->txtReceive->append("停止监听成功");
        ui->btnSend->setEnabled(false);
    }
}

void ServerMain::on_btnSend_clicked()
{
    QString data=ui->txtSend->text();
    if (data==""){return;}

    QString str=ui->cboxClient->currentText();
    int clientID=str.split(":")[0].toInt();
    QString IP=str.split(":")[1];
    int Port=str.split(":")[2].toInt();

    QByteArray da = data.toLatin1();
    server->SendData(clientID,IP,Port,da);

}

void ServerMain::on_btnClear_clicked()
{
    ui->txtReceive->clear();
}
















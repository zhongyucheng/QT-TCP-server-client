#include "tcp_client.h"
#include "ui_tcp_client.h"

tcp_Client::tcp_Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tcp_Client)
{
    ui->setupUi(this);
    this->Initialize();
}

tcp_Client::~tcp_Client()
{
    delete ui;
}


void tcp_Client::Initialize()
{
    ui->btnSend->setEnabled(false);
    ui->txtReceive->setReadOnly(true);
    tcpClient=new QTcpSocket(this);
    tcpClient->abort();//取消原有连接
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(ReadData()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ReadError(QAbstractSocket::SocketError)));
}

void tcp_Client::ReadData()
{
    QByteArray buffer=tcpClient->readAll();
    if (!buffer.isEmpty())
    {
        ui->txtReceive->append("接收数据:"+buffer);

    }
}

void tcp_Client::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    ui->btnConnect->setText("连接");
    ui->txtReceive->append(tr("连接服务器失败,原因:%1").arg(tcpClient->errorString()));
}

void tcp_Client::on_btnConnect_clicked()
{
    if (ui->btnConnect->text()=="连接")
    {
        tcpClient->connectToHost(ui->txtIP->text(),ui->txtPort->text().toInt());
        if (tcpClient->waitForConnected(1000))
        {
            ui->btnConnect->setText("断开");
            ui->txtReceive->append("连接服务器成功");
            ui->btnSend->setEnabled(true);
        }
    }
    else
    {
        tcpClient->disconnectFromHost();
        tcpClient->waitForDisconnected(1000);
        if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000))
        {
            ui->btnConnect->setText("连接");
            ui->txtReceive->append("断开连接成功");
            ui->btnSend->setEnabled(true);
        }
    }
}

void tcp_Client::on_btnClear_clicked()
{
    ui->txtReceive->clear();
}

void tcp_Client::on_btnSend_clicked()
{
    QString data=ui->txtSend->text();

    if (data!="")
    {

            char* data_a ;
            QByteArray ba =data.toLatin1();
            data_a = ba.data();
            tcpClient->write(ba);

    }
}

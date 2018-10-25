#include "tcp_client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tcp_Client w;
    w.setWindowTitle("TCP客户端");
    w.show();

    return a.exec();
}

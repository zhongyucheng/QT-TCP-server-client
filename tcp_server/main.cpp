#include "servermain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerMain w;
    w.setWindowTitle("TCP多线程服务器");
    w.show();

    return a.exec();
}

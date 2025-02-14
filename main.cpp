#include <QCoreApplication>
#include "iwbr_tcpclient.h"
#include "iwbr_tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}

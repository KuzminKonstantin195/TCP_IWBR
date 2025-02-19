#include "iwbr_tcpsocketinterface.h"


IWBR_TcpSocketInterface::IWBR_TcpSocketInterface(QObject *parent, quint8 socket_type)
    : QObject{parent}
{
    this->socket_type = socket_type;
    socket = make_shared<QTcpSocket>(nullptr);
    stream = make_shared<QDataStream>(socket.get());

    //stream->setVersion(QDataStream::Qt_6_8);
}

IWBR_TcpSocketInterface::~IWBR_TcpSocketInterface()
{

}

#include "iwbr_tcpclient.h"

IWBR_TCPClient::IWBR_TCPClient(quint16 id, QString server_ip)
{
    this->id = id;
    this->server_ip = ip;

    // тут будут вызовы конструкторы переделанных сокетов (в них же будут создаваться datastream)
    _sockets[0] = new QTcpSocket;
    _sockets[1] = new QTcpSocket;
    _sockets[2] = new QTcpSocket;

    connect_status =        false;
    transaction_status =    false;
    stack_used =            false;

}

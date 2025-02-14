#include "iwbr_tcpclient.h"

IWBR_TCPClient::IWBR_TCPClient(quint16 id)
{
    this->id = id;
    //this->server_ip = ip;

    // тут будут вызовы конструкторы переделанных сокетов (в них же будут создаваться datastream)
    //_sockets[0] = make_shared<QTcpSocket>();
    //_sockets[1] = make_shared<QTcpSocket>();
    //_sockets[2] = make_shared<QTcpSocket>();

    connect_status[0] = false;
    connect_status[1] = false;
    connect_status[2] = false;

    transaction_status =    false;
    //stack_used = false;

    // устанавливаем соединения флагов коннекта со статусами
    // при подключении
    connect(_sockets[0], &QTcpSocket::connected, this, [this]
            {
                socket_connected(0);
            });
    connect(_sockets[1], &QTcpSocket::connected, this, [this]
            {
                socket_connected(1);
            });
    connect(_sockets[2], &QTcpSocket::connected, this, [this]
            {
                socket_connected(2);
            });
    // отключении
    connect(_sockets[0], &QTcpSocket::disconnected, this, [this]
            {
                socket_disconnected(0);
            });
    connect(_sockets[1], &QTcpSocket::disconnected, this, [this]
            {
                socket_disconnected(1);
            });
    connect(_sockets[2], &QTcpSocket::disconnected, this, [this]
            {
                socket_disconnected(2);
            });

}

IWBR_TCPClient::~IWBR_TCPClient()
{

}

bool IWBR_TCPClient::connect_to_host (QString server_ip, quint16 port)
{
    this->server_ip = server_ip;
    this->port_base = port;

    _sockets[0]->connectToHost(server_ip, port_base);
    _sockets[1]->connectToHost(server_ip, port+1);
    _sockets[2]->connectToHost(server_ip, port+2);

    if (get_connect_status())
    {
        return true;
    }
    return false;
}

bool IWBR_TCPClient::disconnect_from_host ()
{
    _sockets[0]->disconnectFromHost();
    _sockets[1]->disconnectFromHost();
    _sockets[2]->disconnectFromHost();

    if (!get_connect_status())
    {
        return true;
    }
    return false;
}

bool IWBR_TCPClient::get_connect_status ()
{
    if (connect_status[0] && connect_status[1] && connect_status[2])
    {
        return true;
    }

    return false;
}

void IWBR_TCPClient::socket_connected (quint8 num)
{
    connect_status[num] = true;
}

void IWBR_TCPClient::socket_disconnected (quint8 num)
{
    connect_status[num] = false;
}

bool IWBR_TCPClient::send_text  (QString text)
    {return true;}
bool IWBR_TCPClient::send_bytes (QByteArray bytes)
    {return true;}
bool IWBR_TCPClient::send_file  (QString file_name)
    {return true;}



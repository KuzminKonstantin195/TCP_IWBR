#include "iwbr_tcpclient.h"

IWBR_TcpClient::IWBR_TcpClient(quint16 id)
{
    this->id = id;
    //this->server_ip = ip;

    // тут будут вызовы конструкторы переделанных сокетов (в них же будут создаваться datastream)
    _sockets[0] = make_shared<QTcpSocket>(nullptr);
    _sockets[1] = make_shared<QTcpSocket>(nullptr);
    _sockets[2] = make_shared<QTcpSocket>(nullptr);

    connectStatus[0] = false;
    connectStatus[1] = false;
    connectStatus[2] = false;

    transactionStatus =    false;
    //stack_used = false;

    // устанавливаем соединения флагов коннекта со статусами
    // при подключении
    connect(_sockets[0].get(), &QTcpSocket::connected, this, [this]
            {
                socketConnected(0);
            });
    connect(_sockets[1].get(), &QTcpSocket::connected, this, [this]
            {
                socketConnected(1);
            });
    connect(_sockets[2].get(), &QTcpSocket::connected, this, [this]
            {
                socketConnected(2);
            });
    // отключении
    connect(_sockets[0].get(), &QTcpSocket::disconnected, this, [this]
            {
                socketDisconnected(0);
            });
    connect(_sockets[1].get(), &QTcpSocket::disconnected, this, [this]
            {
                socketDisconnected(1);
            });
    connect(_sockets[2].get(), &QTcpSocket::disconnected, this, [this]
            {
                socketDisconnected(2);
            });

}

IWBR_TcpClient::~IWBR_TcpClient()
{

}

bool IWBR_TcpClient::connectToHost (QString ip, quint16 port)
{
    this->serverIP = ip;
    this->portBase = port;

    _sockets[0]->connectToHost(serverIP, portBase);
    _sockets[1]->connectToHost(serverIP, portBase+1);
    _sockets[2]->connectToHost(serverIP, portBase+2);

    if (getConnectStatus())
    {
        return true;
    }
    return false;
}

bool IWBR_TcpClient::disconnectFromHost ()
{
    _sockets[0]->disconnectFromHost();
    _sockets[1]->disconnectFromHost();
    _sockets[2]->disconnectFromHost();

    if (!getConnectStatus())
    {
        return true;
    }
    return false;
}

/*
 * вариант реализации: при вызове функции в нем создается поток с вызовом метода
 * отправки данных в нужном сокете
 *
 * указатель на поток передается в буффер (его лучше переделать в map)
 * с присвоением ему номера (порядкового)
 *
 * создается связь сигналом об окончании выполнения потока (сигнал испускает дочерний
 * сокет) с привязкой к удалению потока из буффера
 *
 */

bool IWBR_TcpClient::sendText  (QString text)
    {
        auto sendThread = make_shared<std::thread>([&]()
        {
            // здесь будет вызов методов отправки в нужном сокете
        });
        threads.push_back(sendThread);
        sendThread->detach();       // полностью отвязываем поток
        return true;
    }
bool IWBR_TcpClient::sendBytes (QByteArray bytes)
    {
        return true;}
bool IWBR_TcpClient::sendFile  (QString file_name)
    {
        return true;}

bool IWBR_TcpClient::stopSending()
    {return true;}

quint16 IWBR_TcpClient::getID ()
{
    return id;
}
void IWBR_TcpClient::setID (quint16 new_id)
{
    /*
     * при наличии активного подключения
     * функция должна уведомить сервер о смене id
     *
     * и поменять, если сервер даст "добро"
     */
    if (getConnectStatus())
    {
        disconnectFromHost();
    }

    id = new_id;
}

QString IWBR_TcpClient::getServerIP ()
{
    return serverIP;
}
void IWBR_TcpClient::setServerIP (QString new_ip)
{
    /*
     * при наличии активного подключения должно произойти отключение
     * и только потом сменить ip
     */
    if (getConnectStatus())
    {
        disconnectFromHost();
    }

    serverIP = new_ip;
}

bool IWBR_TcpClient::getConnectStatus ()
{
    if (connectStatus[0] && connectStatus[1] && connectStatus[2])
    {
        return true;
    }

    return false;
}

// #########################################################################################

void IWBR_TcpClient::socketConnected (quint8 num)
{
    connectStatus[num] = true;
}

void IWBR_TcpClient::socketDisconnected (quint8 num)
{
    connectStatus[num] = false;
}


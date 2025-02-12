#ifndef IWBR_TCPSERVER_H
#define IWBR_TCPSERVER_H

#pragma once
#include "all_headers.h"

using namespace std;

class client;

class IWBR_TCPServer
{
private:
    QMap<quint32, *client> clients;

    quint32 connection_count;


public:
    IWBR_TCPServer();
    ~IWBR_TCPServer();

    bool connect_to_client (QString client_ip, quint16 port);
    bool dicconnect_from_client (quint16 id);
};

#endif // IWBR_TCPSERVER_H

#ifndef IWBR_TCPSERVER_H
#define IWBR_TCPSERVER_H

/*
 * IWBR_TCPServer - сервер протокола TCP IP
 *
 * поддерживает одновременное подключение нескольких клиентов с их идентификацией
 * обрабатывает текстовые сообщения, отправку байтовых данныъ и файлов
 */

#pragma once
#include "all_headers.h"

using namespace std;

struct client;   // структура будет хранить инфу о самом клиенте, о его каналах связи

class IWBR_TCPServer
{
private:
    QTcpServer *_server_obj;                                                // исполняющий объект QTcpServer
    QMap<quint32, shared_ptr<client>> clients;                              // активные клиенты

    QString server_ip;                                                      // ip сервера

public:
    IWBR_TCPServer();                                                       //                                                          статус:
    ~IWBR_TCPServer();                                                      //                                                          статус:

    QString get_ip ();                                                      // получить информацию об ip-сервера                        статус:

    bool connect_to_client (QString client_ip, quint16 port);               // соединиться с конкретным клиентом                        статус:
    bool discconnect_from_client (quint16 id);                              // отключить конкретного клиента                            статус:
    bool disconnect_all ();                                                 // отключить всех активных клиентов                         статус:

    quint32 get_connection_count ();                                        // вовзвращает количество подклюенных клиентов              статус:

    bool send_text (quint16 id, QString text);                              // отправить текстовое сообщение                            статус:
    bool send_bytes (quint16 id, QByteArray bytes);                         // отправить байтовые данные                                статус:
    bool send_file (quint16 id, QString file_name);                         // отправить файл                                           статус:

signals:
    void client_connected ();                                               // сигнал об успешном присоединении клиента                 статус:
    void client_connect_invoice ();                                         // сигнал о запросе клиента на подключение (мб надо)        статус:

    void message_sended ();                                                 // сигнал о завершении отправки сообщения                   статус:

public slots:
    //void ready_read ();

private slots:

};

#endif // IWBR_TCPSERVER_H

#ifndef IWBR_TCPCLIENT_H
#define IWBR_TCPCLIENT_H



/*
 * IWBR_TCPClient - клиент простокола TCP IP
 *
 * поддерживает передачу текстовых сообщений, побайтовых данных и сформированных файлов
 *
 * за каждый тип данных будет отвечать свой экземпляр "кастомного" сокета
 *
 */

#pragma once
#include "all_headers.h"
using namespace std;

class IWBR_TCPClient
{
private:
    quint16 id;                                             // id клиента                                                           статус:
    QString server_ip;                                      // ip-адрес сервера                                                     статус:

    QTcpSocket *_sockets [3];                               // исполняющие сокеты (каждый ответственен за свой формат данных)       статус:

    QVector<shared_ptr<thread>> threads;                    // хранилище потоков                                                    статус:

    bool connect_status;                                    // статус соединения (0 - не подключен, 1 - есть соединение)            статус:
    bool transaction_status;                                // статус наличия активных процессов передачи данных                    статус:

public:

    IWBR_TCPClient(quint16 id, QString server_ip);          //                                                                      статус:
    ~IWBR_TCPClient();                                      //                                                                      статус:

    bool connect_to_host ();                                // подключиться к серверу                                               статус:
    bool disconnect_from_host ();                           // отключиться от сервера                                               статус:

    bool send_text  (QString text);                         // отправка текста                                                      статус:
    bool send_bytes (QByteArray bytes);                     // отправка байтовой                                                    статус:
    bool send_file  (QString file_name);                    // отправка файла                                                       статус:

    bool stop_sending ();                                   // принудительная остановка активных отправлений                        статус:

    quint16 get_id ();                                      // получить текущий id клиента                                          статус:
    void set_id (quint16 new_id);                           // установить ноывй id                                                  статус:

    QString get_server_ip ();                               // получить текущий ip сервера                                          статус:
    void set_server_ip (QString new_ip);                    // установить новый ip сервера (потребуется отключиться)                статус:

    bool get_connect_status ();                             // получить статус подключения                                          статус:
    bool get_transaction_status ();                         // получить статус наличия активных транзакций                          статус:

    template <typename format>
    format get_last_message (quint16 socket_num);           // получить последнее принятое сообщение от выбранного сокета           статус:
signals:
    int message_read_start ();                              // сигнал о начале приема сообщения (возвращает номер сокета)           статус:
    int message_read_end ();                                // сигнал о том, что прием сообщений завершен (возвращает номер сокета) статус:

private slots:


public slots:
    //void ready_read ();

public:
    enum errors_code
    {
        send_error = 1,
        read_error = 2
    };
};

#endif // IWBR_TCPCLIENT_H

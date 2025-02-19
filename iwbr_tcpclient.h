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

//using namespace std;

class IWBR_TcpClient : public QObject
{
    Q_OBJECT

private:
    quint16 id;                                             // id клиента                                                           статус:
    QString serverIP;                                       // ip-адрес сервера                                                     статус:
    quint16 portBase;



    shared_ptr<QTcpSocket> _sockets [3];                    // исполняющие сокеты (каждый ответственен за свой формат данных)       статус:

   // bool TextSocket_connect_status ();

    QVector<shared_ptr<std::thread>> threads;               // хранилище потоков                                                    статус:
    mutex mtx;

    bool connectStatus[3];                                  // статус соединения (0 - не подключен, 1 - есть соединение)            статус:
    bool transactionStatus;                                 // статус наличия активных процессов передачи данных                    статус:

    //stack <QByteArray> messages_stack;                      // возможно понадобится использование стэка сообщений
    //bool stack_used;                                        // флаг, будет ли использоваться стэк

public:

    IWBR_TcpClient(quint16 id);                             //                                                                      статус:
    ~IWBR_TcpClient();                                      //                                                                      статус:

    bool connectToHost (QString ip, quint16 port);          // подключиться к серверу                                               статус: есть
    bool disconnectFromHost ();                             // отключиться от сервера                                               статус: есть

    bool sendText  (QString text);                          // отправка текста                                                      статус:
    bool sendBytes (QByteArray bytes);                      // отправка байтовой                                                    статус:
    bool sendFile  (QString file_name);                     // отправка файла                                                       статус:

    bool stopSending ();                                    // принудительная остановка активных отправлений                        статус:

    quint16 getID ();                                       // получить текущий id клиента                                          статус: готово
    void setID (quint16 new_id);                            // установить ноывй id                                                  статус: есть

    QString getServerIP ();                                 // получить текущий ip сервера                                          статус: готово
    void setServerIP (QString new_ip);                      // установить новый ip сервера (потребуется отключиться)                статус: готово

    bool getConnectStatus ();                               // получить статус подключения                                          статус: готово
    bool getTransactionStatus ();                           // получить статус наличия активных транзакций                          статус:

    //bool getStackUsedStatus ();                             // получить статус использования стэка сообщений                        статус:
    //void setStackUsedStatus (bool state);                   // установить статус использования тега сообщений                       статус:

signals:
    int messageReadStart ();                                // сигнал о начале приема сообщения (возвращает номер сокета)           статус:
    int messageReadEnd ();                                  // сигнал о том, что прием сообщений завершен (возвращает номер сокета) статус:

private slots:
    //template <typename retFormat>
    //retFormat getLastMessage (quint16 socket_num);        // получить последнее принятое сообщение от выбранного сокета         статус:

    void socketConnected (quint8 num);                      // реация на соединения сокета                                          статус: готово
    void socketDisconnected (quint8 num);                   // реакция на дисконнект сокета                                         статус: готово
public slots:
    //void readyRead ();


public:
    enum errors_codes
    {
        send_error = 1,
        read_error
    };
};

#endif // IWBR_TCPCLIENT_H

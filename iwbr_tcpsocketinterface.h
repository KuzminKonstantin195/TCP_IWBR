#ifndef IWBR_TCPSOCKETINTERFACE_H
#define IWBR_TCPSOCKETINTERFACE_H

#include "all_headers.h"

using namespace std;

class IWBR_TcpSocketInterface : public QObject
{
    Q_OBJECT

    quint8 socket_type;

    shared_ptr<QTcpSocket> socket;
    shared_ptr<QDataStream> stream;



public:
    IWBR_TcpSocketInterface(QObject *parent, quint8 socket_type);
    ~IWBR_TcpSocketInterface();

    bool getStreamStatus;

signals:
    //virtual void fullMessageReceived (QByteArray* data);

private slots:

public slots:
    //void readyRead ();


};

#endif // IWBR_TCPSOCKETINTERFACE_H

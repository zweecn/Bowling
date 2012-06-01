#ifndef _FRONT_TCP_CLIENT_H
#define _FRONT_TCP_CLIENT_H

#include <QTcpSocket>
#include <QtNetwork>
#include <QMessageBox>
#include <QString>
#include <QMap>
#include "dataInfo.h"
#include "rowInfo.h"

class PortIp
{
public:
    int port;
    QString ip;
};

class FrontTcpClient:public QWidget
{
Q_OBJECT
public:
    FrontTcpClient(QWidget *parent=0);

signals:
	void dataReceived(RowInfo rowInfo);
	void dataReceived(int restCount);
    void closeSignal();
public slots:
    void send();
    void receive();
    void connectToServer(int row, int service, RowInfo info);
    void connectToServer(int row, int service, int rest);
    void closeConnection();
    void displayError(QAbstractSocket::SocketError socketError);
private:
    QTcpSocket *tcpSocket;
    void initConnection();
    quint16 blockSize;
    quint16 sendTag, recvTag, restCnt;
    RowInfo rowInfo;
    int rowId;
    QMap<int, PortIp> portIpTable;
};

#endif // FrontTcpClient_H

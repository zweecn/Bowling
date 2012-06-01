#ifndef _TRIP_SERVER_H
#define _TRIP_SERVER_H
#include <QDate>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include "dataInfo.h"
#include "front/rowInfo.h"

class CustomerClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    CustomerClientSocket(QObject *parent = 0);
signals:
    void changeRow(RowInfo info);
    void beginPlay(int restCount);
    void addMoney(int restCount);
    void dissMiss();

private slots:
    void readClient();
private:
    quint16 nextBlockSize;
    quint16 serviceFlag;
    quint16 clientRestCount;
};


class CustomerTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    CustomerTcpServer(QObject *parent = 0);
signals:
    void changeRow(RowInfo info);
    void beginPlay(int restCnt);
    void addMoney(int restCount);
    void dissMiss();
public slots:
    void sendRestCount(int restCnt);
    void sendRowInfo(RowInfo info);
    void sendAddMoney(int restCnt);
    void sendDissMiss();
protected:
    void incomingConnection(int socketId);
};

#endif

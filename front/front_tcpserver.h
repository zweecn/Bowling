#ifndef _FRONT_TCP_SERVER_H
#define _FRONT_TCP_SERVER_H
#include <QDate>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include "dataInfo.h"
#include "rowInfo.h"

typedef dataTransform::GoodsInfo GoodsInfo;
typedef dataTransform::ScoreInfo ScoreInfo;

class FrontClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    FrontClientSocket(QObject *parent = 0);
signals:
    void callService(int rowId);
    void scoreChanged(int rowId);
    void endOne(int rowId, int rest);
    void buyGoodsChanged(int rowId);
private slots:
        void readClient();
private:
    /*void generateRandomTrip(const QString &from, const QString &to,
        const QDate &date, const QTime &time);*/
    quint16 nextBlockSize;

    quint16 serviceFlag, toClientFlag;
    QString ipAddress;
    quint16 rowId;
    RowInfo rowInfo;//, rowInfoUpdate;

    void sentToClient(int tag, const int restCount);//, int rowId);
    void sentToClient(int tag);


};


class FrontServer : public QTcpServer
{
    Q_OBJECT
public:
    FrontServer(QObject *parent = 0);
signals:
    void scoreChanged(int rowId);
    void endOne(int rowId, int rest);
    void buyGoodsChanged(int rowId);
public slots:
    void sendSignal(int rowId);
    void sendGoodsSignal(int rowId);
    void sendEndOne(int rowId, int rest);
protected:
    void incomingConnection(int socketId);
};



#endif

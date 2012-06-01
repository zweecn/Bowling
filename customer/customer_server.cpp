#include "customer_server.h"
#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <assert.h>
#include <QDebug>
#include "datainfo.h"

CustomerTcpServer::CustomerTcpServer(QObject *parent) : QTcpServer(parent)
{
    //listen(QHostAddress::Any,port);
}

void CustomerTcpServer::incomingConnection(int socketId)
{
    CustomerClientSocket *socket = new CustomerClientSocket(this);
    socket->setSocketDescriptor(socketId);
    QObject::connect(socket, SIGNAL(changeRow(RowInfo)), this, SLOT(sendRowInfo(RowInfo)));
    QObject::connect(socket, SIGNAL(beginPlay(int)), this, SLOT(sendRestCount(int)));
    QObject::connect(socket, SIGNAL(addMoney(int)), this, SLOT(sendAddMoney(int)));
    QObject::connect(socket, SIGNAL(dissMiss()), this, SLOT(sendDissMiss()));
}

void CustomerTcpServer::sendRowInfo(RowInfo info)
{
    emit changeRow(info);
}

void CustomerTcpServer::sendRestCount(int restCnt)
{
    emit beginPlay(restCnt);
}

void CustomerTcpServer::sendAddMoney(int restCnt)
{
    emit addMoney(restCnt);
}

void CustomerTcpServer::sendDissMiss()
{
    emit dissMiss();
}


CustomerClientSocket::CustomerClientSocket(QObject *parent)
: QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));

    nextBlockSize = 0;
}

void CustomerClientSocket::readClient()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_4_1);

    if (nextBlockSize == 0) {
        if (bytesAvailable() < sizeof(quint16))
            return;  //继承的socket类，所以可以直接用bytesAvailable()
        in >> nextBlockSize;
    }
    if (bytesAvailable() < nextBlockSize)
        return;

    in >> serviceFlag;
    in >> clientRestCount;

    quint16 totalPlayerCount16, currentPlayerNo16;
    quint16 turn16, score16;
    qint16 bt16;
    RowInfo rowInfo;

    switch (serviceFlag)
    {
    case dataTransform::ANS_YES_YOU_CAN_BEGIN:
        emit beginPlay(clientRestCount);
        break;
    case dataTransform::ANS_NO_DO_NOT_BEGIN:
        clientRestCount = 0;
        break;
    case dataTransform::ANS_AFTER_ADD_MONEY:
        emit addMoney(clientRestCount);
        break;
    case dataTransform::ANS_DISMISS:
        emit dissMiss();
        break;
    case dataTransform::ANS_YOU_CAN_EXCHANGE_ROW:
          in >> totalPlayerCount16
             >> currentPlayerNo16;
        rowInfo.restCount = clientRestCount; //剩余局数
        //rowInfo.useType = useType16;
        assert(totalPlayerCount16>=0);
        rowInfo.totalPlayerCount = totalPlayerCount16;
        rowInfo.currentPlayerNo = (currentPlayerNo16 < totalPlayerCount16 ? currentPlayerNo16 : 0);
        rowInfo.scoreInfo.resize(totalPlayerCount16);
        for (int i=0; i<rowInfo.totalPlayerCount; i++)
        {
            in	>> turn16;
            rowInfo.scoreInfo[i].turn = turn16;

            for (int j=0; j<dataTransform::SCORE_SIZE; j++)
            {
                in >> score16
                    >> rowInfo.scoreInfo[i].str[j];
                rowInfo.scoreInfo[i].score[j] = score16;
                if (rowInfo.scoreInfo[i].str[j]=="-")
                    rowInfo.scoreInfo[i].str[j].clear();
            }

            for (int j=0; j<dataTransform::BT_ROW_SIZE; j++)
            {
                for (int k=0; k<dataTransform::SCORE_SIZE; k++)
                {
                    in >> bt16;
                    rowInfo.scoreInfo[i].bt[j][k] = bt16;
                    //qDebug() << "In bt " << j << " " << k << " " << rowInfo.scoreInfo[i].bt[j][k];
                }
            }

        }
        emit changeRow(rowInfo);
        break;
    default:
        //QMessageBox::critical(NULL, "错误", "\n未识别信息\n" + servString + "\n\n");
        qDebug() << "Unknow information";
        break;
    } //end switch

    quint32 temp;
    while (bytesAvailable())
    {
        in >> temp;
    }
    close();
    nextBlockSize = 0;
}

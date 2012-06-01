#include "front_tcpserver.h"
#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <assert.h>
#include <QDebug>
#include <QSqlQuery>
#include <QDateTime>
#include <QSqlError>

FrontServer::FrontServer(QObject *parent) : QTcpServer(parent)
{
    //listen(QHostAddress::Any,port);
}

void FrontServer::incomingConnection(int socketId)
{
    FrontClientSocket *socket = new FrontClientSocket(this);
    socket->setSocketDescriptor(socketId);
    QObject::connect(socket, SIGNAL(scoreChanged(int)), this, SLOT(sendSignal(int)));
    QObject::connect(socket, SIGNAL(buyGoodsChanged(int)), this, SLOT(sendGoodsSignal(int)));
    QObject::connect(socket, SIGNAL(endOne(int, int)), this, SLOT(sendEndOne(int, int)));
}
void FrontServer::sendSignal(int rowId)
{
    //QString temp;
    //temp.setNum(rowId);
    //QMessageBox::critical(0, "内部信号", "serve收到信号，显示球道号 " +temp + "\n\n");
    emit scoreChanged(rowId);

}

void FrontServer::sendGoodsSignal(int rowId)
{
    emit buyGoodsChanged(rowId);
}

void FrontServer::sendEndOne(int rowId, int rest)
{
    emit endOne(rowId, rest);
}

FrontClientSocket::FrontClientSocket(QObject *parent)
: QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    nextBlockSize = 0;
}

void FrontClientSocket::readClient()
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
    in >> rowId;

    QString rowIdString, servString;
    rowIdString.setNum(rowId);
    servString.setNum(serviceFlag);

    quint16  totalPlayerCount16, currentPlayerNo16;
    quint16 turn16, score16;
    quint16 goodsTypeSize16, goodsId16, goodsCount16;
    qint16 bt16;
    bool openFlag = rowInfo.readInfo(rowId);
    if (!openFlag)
    {
        close();
        return;
    }
    QString tempS;
    QSqlQuery sql;
    switch (serviceFlag)
    {
    case dataTransform::END_ONE:
        in >> totalPlayerCount16;
        if (totalPlayerCount16==0 || rowInfo.scoreInfo.size()<totalPlayerCount16)
            totalPlayerCount16 = rowInfo.scoreInfo.size();
        for (int i=0; rowInfo.vipId!="" && i<totalPlayerCount16; i++)
        {
            int xCnt = 0;
            int hxCnt = 0;
            int score = rowInfo.scoreInfo[i].score[dataTransform::SCORE_SIZE-1];
            for (int j=0; j<dataTransform::SCORE_SIZE; j++)
            {
                if (rowInfo.scoreInfo[i].str[j]=="X")
                    xCnt++;
                if (rowInfo.scoreInfo[i].str[j]=="?\\")
                    hxCnt++;
            }

            sql.prepare("INSERT INTO score_record VALUES (?, ?, ?, ?, ?);");
            sql.addBindValue(rowInfo.vipId.toInt());
            sql.addBindValue(QDateTime::currentDateTime().toString("yy-MM-dd hh:mm"));
            sql.addBindValue(score);
            sql.addBindValue(xCnt);
            sql.addBindValue(hxCnt);
            sql.exec();
            //if (!sql.exec())
            //    qDebug() << "Insert vip history error " << sql.lastError().text();
        }

        rowInfo.totalPlayerCount = totalPlayerCount16;
        if (rowInfo.totalPlayerCount<=rowInfo.restCount)
            rowInfo.restCount -= rowInfo.totalPlayerCount;
        else
            rowInfo.restCount = 0;
        //tempS.setNum(rowInfo.scoreInfo.size());
        //QMessageBox::critical(0, "NULL", "总局数：" + tempS );
        rowInfo.totalPlayerCount = 0;
        rowInfo.scoreInfo.clear();
        rowInfo.currentPlayerNo = 0;
        rowInfo.writeInfo(rowId);
        if (rowInfo.restCount==0)
        {
            sentToClient(dataTransform::ANS_NO_DO_NOT_BEGIN, 0);
            emit endOne(rowId, 0);
        }
        else
        {

            sentToClient(dataTransform::ANS_YES_YOU_CAN_BEGIN, rowInfo.restCount);
            emit endOne(rowId, rowInfo.restCount);
        }
        break;
    case dataTransform::ROW_SCORE:
          in >> totalPlayerCount16
             >> currentPlayerNo16;
        if (totalPlayerCount16==0 || currentPlayerNo16>=totalPlayerCount16)
            currentPlayerNo16 = 0;
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
        if (rowInfo.restCount==0 && rowInfo.state=="占用")
        {
            rowInfo.state = "空闲";
        }
        rowInfo.writeInfo(rowId);
        emit scoreChanged(int(rowId));

        //QMessageBox::critical(0, "收到得分请求", "\n收到得分,写入文件，发出球道信息改变信号\n");
        break;
    case dataTransform::CALL_GOODS:
        in >> goodsTypeSize16;
        assert(goodsTypeSize16>=0);
        rowInfo.buyGoodsInfo.goodsTypeSize = goodsTypeSize16;
        rowInfo.buyGoodsInfo.goodsId.resize(goodsTypeSize16);
        rowInfo.buyGoodsInfo.goodsCount.resize(goodsTypeSize16);
        for (int i=0; i<rowInfo.buyGoodsInfo.goodsTypeSize; i++)
        {
            in >> goodsId16;
            rowInfo.buyGoodsInfo.goodsId[i] = goodsId16;
            in >> goodsCount16;
            rowInfo.buyGoodsInfo.goodsCount[i] = goodsCount16;

            //qDebug() << "编号:" << goodsId16 << "  数量:" << goodsCount16;
        }
        rowInfo.writeInfo(rowId);
        emit buyGoodsChanged(int(rowId));

        break;
    case dataTransform::CALL_SERVICE:
        QMessageBox::information(NULL, "新信息", "\n" + rowIdString + " 号球道呼叫\n");
        emit callService(rowId);
        break;
    default:
        //QMessageBox::critical(NULL, "错误", "\n未识别信息\n" + servString + "\n\n");
        //qDebug() << "Unknow information";
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

void FrontClientSocket::sentToClient(int tag)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_1);

    out << quint16(0);
    out << quint16(tag);

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    write(block);
}

void FrontClientSocket::sentToClient(int tag, const int restCount)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_1);

    out << quint16(0);
    out << quint16(tag);
    out << quint16(restCount);

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    write(block);
}

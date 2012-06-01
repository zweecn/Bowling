#include "customer_tcpclient.h"
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QList>

CustomerTcpClient::CustomerTcpClient(QWidget *parent) :
QWidget(parent)
{
    QFile file("server_port_ip.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "File 'server_port_ip.txt' open failed" ;
        return;
    }

    QTextStream in(&file);
    if (!in.atEnd())
    {
         in >> serverIP >> port;
    }
    file.close();

	tcpSocket=new QTcpSocket(this);
	initConnection();
}

void CustomerTcpClient::initConnection()
{
	connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(closeConnection()));
	connect(tcpSocket,SIGNAL(connected()),this,SLOT(send()));
	connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receive()));
	connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
}

void CustomerTcpClient::receive()
{
	QDataStream in(tcpSocket);
	in.setVersion(QDataStream::Qt_4_1);
	QByteArray block;
	if (blockSize == 0) 
	{
		if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
			return;
		in >> blockSize;
	}

	if (tcpSocket->bytesAvailable() < blockSize)
		return;

    in >> recvTag;
    quint16 restCount16 = 0;
	in >> restCount16;
    //qDebug() << "receive rescnt" << restCount16;
	QString flag; 
	flag.setNum(restCount16);
    switch (recvTag)
	{
	case dataTransform::ANS_YES_YOU_CAN_BEGIN:
		emit dataReceived(restCount16);
		break;
	case dataTransform::ANS_NO_DO_NOT_BEGIN:
		emit dataReceived(0);
		break;
	default:
		break;
	}
}

void CustomerTcpClient::send()
{
	QByteArray block;

	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_1);

	out << quint16(0);
    out << quint16(sendTag);
	out << quint16(rowId);

	rowInfo.totalPlayerCount = rowInfo.totalPlayerCount < rowInfo.scoreInfo.size() 
		? rowInfo.totalPlayerCount : rowInfo.scoreInfo.size() ;
	rowInfo.currentPlayerNo = rowInfo.currentPlayerNo < rowInfo.totalPlayerCount
		? rowInfo.currentPlayerNo : 0;

    switch (sendTag)
	{
	case dataTransform::END_ONE:
        out	<< quint16(rowInfo.totalPlayerCount);
		break;
	case dataTransform::ROW_SCORE:
        out	<< quint16(rowInfo.totalPlayerCount)
			<< quint16(rowInfo.currentPlayerNo);
		for (int i=0; i<rowInfo.totalPlayerCount; i++)
		{
			out	<< quint16(rowInfo.scoreInfo[i].turn);

			for (int j=0; j<dataTransform::SCORE_SIZE; j++)
			{
				out << quint16(rowInfo.scoreInfo[i].score[j])
					<< (rowInfo.scoreInfo[i].str[j]=="" ? "-" : rowInfo.scoreInfo[i].str[j]);
			}

			for (int j=0; j<dataTransform::BT_ROW_SIZE; j++)
			{
				for (int k=0; k<dataTransform::SCORE_SIZE; k++)
				{
					out << qint16(rowInfo.scoreInfo[i].bt[j][k]);
				}
			}
		}
		break;
	case dataTransform::CALL_GOODS:
		rowInfo.buyGoodsInfo.goodsTypeSize = rowInfo.buyGoodsInfo.goodsId.size() < rowInfo.buyGoodsInfo.goodsCount.size()
			? rowInfo.buyGoodsInfo.goodsId.size() : rowInfo.buyGoodsInfo.goodsCount.size();
		out << quint16(rowInfo.buyGoodsInfo.goodsTypeSize);
		for (int i=0; i<rowInfo.buyGoodsInfo.goodsTypeSize; i++)
		{
			out << quint16(rowInfo.buyGoodsInfo.goodsId[i]);
			out << quint16(rowInfo.buyGoodsInfo.goodsCount[i]);
            //total.setNum(rowInfo.buyGoodsInfo.goodsCount[i]);
			//QMessageBox::critical(0, "数量", "数量 " + total);
		}
    case dataTransform::CALL_SERVICE:

		break;
	default:
		break;
	}

	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	tcpSocket->write(block);
}


void CustomerTcpClient::displayError(QAbstractSocket::SocketError socketError)
{
	switch (socketError) 
	{
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(0, tr("客户端"),
            tr("未找到服务器"));
		break;
	case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(0, tr("客户端"),
            tr("连接失败，请确认服务器是否开启，以及端口是否正确"));
		break;
	default:
        QMessageBox::information(0, tr("客户端"),
            tr("错误信息: %1.")
			.arg(tcpSocket->errorString()));
	}
}

void CustomerTcpClient::connectToServer(int row, int service, RowInfo info)
{
	rowId = row;
    sendTag = service;
	rowInfo = info;
	blockSize=0;

	tcpSocket->abort();
//    if (info.totalPlayerCount==0 || info.totalPlayerCount>=info.scoreInfo.size() || info.scoreInfo.size()==0)
//        return;
    tcpSocket->connectToHost(serverIP, port);
}

void CustomerTcpClient::connectToServer(int row, int service)
{
	rowId = row;
    sendTag = service;
	blockSize=0;
	tcpSocket->abort();
    tcpSocket->connectToHost(serverIP, port);
}

void CustomerTcpClient::connectToServer(int row, int service, int rest)
{
    rowId = row;
    sendTag = service;
    rowInfo.restCount = rest;
    blockSize=0;
    tcpSocket->abort();
    tcpSocket->connectToHost(serverIP, port);
}



void CustomerTcpClient::closeConnection()
{
	tcpSocket->close();
}


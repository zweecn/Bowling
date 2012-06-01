#include "front_tcpclient.h"
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QList>

FrontTcpClient::FrontTcpClient(QWidget *parent) : QWidget(parent)
{
    QFile file("id_ip_port.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "File 'id_ip_port.txt' open failed" ;
        return;

    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        in >> rowId;
        in >> portIpTable[rowId].ip >> portIpTable[rowId].port;
    }
    file.close();

    tcpSocket=new QTcpSocket;
	initConnection();
}

void FrontTcpClient::initConnection()
{
    QObject::connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(closeConnection()));
    QObject::connect(tcpSocket,SIGNAL(connected()),this,SLOT(send()));
    QObject::connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receive()));
    QObject::connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
}

void FrontTcpClient::receive()
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
	//in >> rowId;

    quint16 restCount16, totalPlayerCount16, currentPlayerNo16;
    quint16 turn16, score16;
	quint16 goodsTypeSize16, goodsId16, goodsCount16;
	qint16 bt16;
	in >> restCount16;
	QString flag; 
	flag.setNum(restCount16);
	//QMessageBox::critical(0, "BGEIN", "Come Back  \n" + flag + "\n\n");
    switch (recvTag)
	{
	case dataTransform::ANS_YES_YOU_CAN_BEGIN:

		emit dataReceived(restCount16);
		//QMessageBox::critical(0, "BGEIN", "Yes, you can begin.\n");
		break;
	case dataTransform::ANS_NO_DO_NOT_BEGIN:
		//in >> restCount16;
		//QMessageBox::critical(0, "BGEIN", "No, you can not begin.\n");
		emit dataReceived(0);
		break;
    case dataTransform::ANS_CLEAR_SCORE:
        emit dataReceived(dataTransform::ANS_CLEAR_SCORE);
        break;
    case dataTransform::ANS_INIT_SCORE:
		//in >> restCount16
		in	>> rowInfo.restTime
			//>> rowInfo.state
			//>> rowInfo.type
			//>> useType16
			>> totalPlayerCount16
			>> currentPlayerNo16;
		rowInfo.type = "";
		rowInfo.state = "";
		rowInfo.restCount = restCount16;
		rowInfo.useType = 0;
		rowInfo.totalPlayerCount = totalPlayerCount16;
		rowInfo.currentPlayerNo = currentPlayerNo16;

		rowInfo.scoreInfo.resize(totalPlayerCount16);
		for (int i=0; i<rowInfo.totalPlayerCount; i++)
		{
			//in >> theEndFlag16
			in	>> turn16;

			rowInfo.scoreInfo[i].theEndFlag = 0;
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
				}
			}
		}
		in >> goodsTypeSize16;
		rowInfo.buyGoodsInfo.goodsTypeSize = goodsTypeSize16;
		rowInfo.buyGoodsInfo.goodsId.resize(goodsTypeSize16);
		rowInfo.buyGoodsInfo.goodsCount.resize(goodsTypeSize16);
		for (int i=0; i<rowInfo.buyGoodsInfo.goodsTypeSize; i++)
		{
			in >> goodsId16;
			rowInfo.buyGoodsInfo.goodsId[i] = goodsId16;
			in >> goodsCount16;
			rowInfo.buyGoodsInfo.goodsCount[i] = goodsCount16;
		}
		emit dataReceived(rowInfo);
		break;
	default:
		break;
	}
}

void FrontTcpClient::send()
{
    //QMessageBox::critical(0, "前台", "前台服务员发送信息");
	QByteArray block;

	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_1);

	out << quint16(0);
    out << quint16(sendTag);
    rowInfo.readInfo(rowId);

	rowInfo.totalPlayerCount = rowInfo.totalPlayerCount < rowInfo.scoreInfo.size() 
		? rowInfo.totalPlayerCount : rowInfo.scoreInfo.size() ;
	rowInfo.currentPlayerNo = rowInfo.currentPlayerNo < rowInfo.totalPlayerCount
		? rowInfo.currentPlayerNo : 0;
    switch (sendTag)
	{
    case dataTransform::ANS_YES_YOU_CAN_BEGIN:
        out << quint16(restCnt);
        break;
    case dataTransform::ANS_NO_DO_NOT_BEGIN:
        out << quint16(0);
        break;
    case dataTransform::ANS_AFTER_ADD_MONEY:
        out << quint16(restCnt);
        break;
    case dataTransform::ANS_DISMISS:
        out << quint16(0);
        break;
    case dataTransform::ANS_YOU_CAN_EXCHANGE_ROW:
        //QMessageBox::critical(0, "前台", "前台服务员发送交换后球道信息");
            out << quint16(rowInfo.restCount)
               << quint16(rowInfo.totalPlayerCount)
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
	default:
       // qDebug() << "Unknow information";
		break;
	}
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));
	tcpSocket->write(block);
}


void FrontTcpClient::displayError(QAbstractSocket::SocketError socketError)
{
	switch (socketError) 
	{
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(0, tr("客户端"),
            tr("未找到服务器,请修改id_ip_port.txt配置文件, 格式为 球道号、IP、端口"));
		break;
	case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(0, tr("客户端"),
            tr("连接失败，请确认球道处机器是否开启，以及端口是否正确"));
		break;
	default:
        QMessageBox::information(0, tr("客户端"),
            tr("错误信息: %1.")
			.arg(tcpSocket->errorString()));
	}
}

void FrontTcpClient::connectToServer(int row, int service, RowInfo info)
{
    rowId = row;
    sendTag = service;
	rowInfo = info;

	blockSize=0;
	tcpSocket->abort();
    tcpSocket->connectToHost(portIpTable[row].ip, portIpTable[row].port);
}

void FrontTcpClient::connectToServer(int row, int service, int rest)
{
    rowId = row;
    sendTag = service;
    restCnt = rest;
	blockSize=0;
	tcpSocket->abort();
//    PortIp tmpP;
//    tmpP.ip=portIpTable.value(row).ip;
//    qDebug()<<tmpP.ip;
    tcpSocket->connectToHost(portIpTable[row].ip, portIpTable[row].port);
    //tcpSocket->connectToHost("localhost",4567);
}

void FrontTcpClient::closeConnection()
{
	tcpSocket->close();
}

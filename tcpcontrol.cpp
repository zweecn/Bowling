#include "tcpcontrol.h"
#include <QDebug>
#include <QList>

TcpControl::TcpControl(QWidget *parent) :
    QWidget(parent)
{
    init();
    tcpSocket=new QTcpSocket(this);
    initConnection();
}

void TcpControl::initConnection()
{
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(closeConnection()));
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(send()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receive()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
}

void TcpControl::receive()
{
        QDataStream in(tcpSocket);
         in.setVersion(QDataStream::Qt_4_0);

         if (blockSize == 0) {
             if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
                 return;

             in >> blockSize;
         }

         if (tcpSocket->bytesAvailable() < blockSize)
             return;
        int count;
        in >> count;
        QPointF pos;
        updateNode tmpNode;
        QString ipAddress;
        for(int i=0;i<count;i++)
        {
            in>>ipAddress>>pos;
//            if(!entitiesPos->entitiesPosInfo.contains(ipAddress))
//            {
//                dirty=true;
//                entitiesPos->updateInfo.clear();
//                tmpNode.id=ipAddress;
//                tmpNode.pos.setX(pos.x());
//                tmpNode.pos.setY(pos.y());
//                entitiesPos->updateInfo.append(tmpNode);
//            }
            if(!ipAddress.compare(ip))
            {
                continue;
            }
            entitiesPos->entitiesPosInfo.insert(ipAddress,pos);
        }
        emit updateEntitiesPos();

}

void TcpControl::send()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out<<ip;
    out<<pos;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    tcpSocket->write(block);
}

void TcpControl::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
         case QAbstractSocket::RemoteHostClosedError:
             break;
         case QAbstractSocket::HostNotFoundError:
             QMessageBox::information(0, tr("Client"),
                                      tr("The host was not found. Please check the "
                                         "host name and port settings."));
             break;
         case QAbstractSocket::ConnectionRefusedError:
             QMessageBox::information(0, tr("Client"),
                                      tr("The connection was refused by the peer. "
                                         "Make sure the fortune server is running, "
                                         "and check that the host name and port "
                                         "settings are correct."));
             break;
         default:
             QMessageBox::information(0, tr("Client"),
                                      tr("The following error occurred: %1.")
                                      .arg(tcpSocket->errorString()));
         }
}

void TcpControl::connectToServer(QString ipAddress,int port ,QPointF position)
{
        setPos(position);
        blockSize=0;
        tcpSocket->abort();
        tcpSocket->connectToHost(ipAddress,port);
}

void TcpControl::closeConnection()
{
    tcpSocket->close();
}

void TcpControl::init()
{
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ip = ipAddressesList.at(i).toString();
            break;
        }
    }

}

void TcpControl::setPos(QPointF position)
{
    pos.setX(position.x());
    pos.setY(position.y());
}

void TcpControl::setEntitiesPosDate(EntitiesPosDate *entities)
{
    entitiesPos=entities;
}

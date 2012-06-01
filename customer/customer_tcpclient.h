#ifndef CustomerTcpClient_H
#define CustomerTcpClient_H

#include <QWidget>
#include <QTcpSocket>
#include <QtNetwork>
#include <QMessageBox>
#include  <QString>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "dataInfo.h"

#include "front/rowInfo.h"

class CustomerTcpClient : public QWidget
{
Q_OBJECT
public:
    CustomerTcpClient(QWidget *parent = 0);
signals:
    void dataReceived(int rest);
public slots:
    void send();
    void receive();
    void connectToServer(int row, int service, RowInfo info);
	void connectToServer(int row, int service);
    void connectToServer(int row, int service, int rest);
    void closeConnection();
    void displayError(QAbstractSocket::SocketError socketError);
private:
    QTcpSocket *tcpSocket;
    void initConnection();
    quint16 blockSize;

    int port;
    QString serverIP;

    quint16 sendTag, recvTag;
	quint16 rowId;
	RowInfo rowInfo;
};

#endif // CustomerTcpClient_H

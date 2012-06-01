#ifndef TCPCONTROL_H
#define TCPCONTROL_H

#include <QWidget>
#include <QTcpSocket>
#include <QtNetwork>
#include <QMessageBox>
#include  <QString>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPointF>
#include "entitiesposdate.h"
class TcpControl : public QWidget
{
Q_OBJECT
public:
    TcpControl(QWidget *parent = 0);
    void setPos(QPointF position);
    void setEntitiesPosDate(EntitiesPosDate *entities);

signals:
    //void updateEntities();
    void updateEntitiesPos();
public slots:
    void send();
    void receive();
    void connectToServer(QString ipAddress,int port,QPointF position);
    void closeConnection();
    void displayError(QAbstractSocket::SocketError socketError);
    void init();
private:
    QTcpSocket *tcpSocket;
    void initConnection();
    quint16 blockSize;
    QString ip;
    QPointF pos;
    EntitiesPosDate *entitiesPos;
};

#endif // TCPCONTROL_H

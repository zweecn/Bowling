#ifndef CHANNELUI_H
#define CHANNELUI_H

#include <QtCore/QVariant>
#include <QtGui/QApplication>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QList>
#include <QDebug>
#include <QMessageBox>
#include <QStackedWidget>
#include <QInputDialog>
#include <QTime>
#include <fstream>
#include "datainfo.h"
#include "front/rowInfo.h"
#include "customer_server.h"
#include "customer_tcpclient.h"

class Channel : public QWidget
{
    Q_OBJECT

public:
	QWidget *layOutWidget;
    QWidget *foodWidget;
    QTableWidget *foodTableWidget;
	QPushButton *okPushButton, *acc, *cncel;
    QWidget *historyWidget;
    QTableWidget *historyTableWidget;
    QWidget *channelWidget;
    QWidget *channelNumWidget;
	QStackedWidget *stackWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label;
	QLabel *labelNO;
    QSpacerItem *horizontalSpacer_6;
    QComboBox *comboBox;
	QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_8;
    QWidget *widget1;
	QVBoxLayout *verticalLayout, *verticalLayout1, *verticalLayout2, *verticalLayout3, *verticalLayout4;
    QVBoxLayout *channelLayout, *gridLayout;
	QGridLayout *gridLayout1, *gridLayout2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *channelPushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *historyPushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *foodPushButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *callPushButton;
    QSpacerItem *horizontalSpacer_5, *horizontalSpacer_9, *horizontalSpacer_10, *horizontalSpacer_11;
    QSpacerItem *verticalSpacer_2, *verticalSpacer_3, *verticalSpacer_4, *verticalSpacer_5, *verticalSpacer_6;
	QSpacerItem *verticalSpacer_7, *verticalSpacer_8, *verticalSpacer_9;
    QList<QWidget *> widgetList;
    QList<QLabel *> labelListA;
	QList<QLabel *> labelListB;
	int score[10][3];
	QString str[10][3];
	int turn;
	int playerNO;
	int bt[4][10][3];
    bool breakFlag;
	QList<QString> historyStat;
	QList<QString> historyDetail;
	int maxCount;
	
	int getNum();
	void initScore();
	void showStat(const int n, const int p);
	void getScore(const int n, const int p);

    Channel(QWidget *parent = 0);
    void initChannelLayout();
    void initConnection();
	void getRowInfo(const int n, const int p);
public slots:
	void showScore();
    void getPushButtonDown();
    void callService();
    void getChannelShow(int num);
	void getHistoryShow(int r, int c);
	void writeHistory(QString name, int currentP, int historyScore);
	void orderService();
	void orderNetwork();
	void unableCombobox();
	void initRestCount(int restCnt);
    void addRestCount(int restCnt);
	void intRowinfo(RowInfo info);
    void clearRowinfo();
    void setPortAndID(int port,int id);

private:
	std::ifstream fin;
	int restCount;
	int number;
        int port;
	int currentPlayer;
	RowInfo rowInformation;
    CustomerTcpClient tcpCtrl;
    CustomerTcpServer* server;
};

#endif // CHANNELUI_H

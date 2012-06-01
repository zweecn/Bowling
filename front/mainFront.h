#ifndef _MAIN_FRONT_H
#define _MAIN_FRONT_H
#include <QMap>
#define ROW_SIZE 20

#include "rowInfo.h"
#include "ui_mainFront.h"

#include "vipLookup.h"
#include "vipRegister.h"
#include "vipRecharge.h"
#include "changeRow.h"
#include "front_check_book.h"
#include "addTeachInfo.h"
#include "teachInfo.h"
#include "goodsSale.h"
#include "front_tcpclient.h"
#include "login.h"
//#include "scoreInformation.h"
#include "front_tcpserver.h"
#include <QFile>
#include <QTextStream>


class MainFront : public QWidget
{
    Q_OBJECT

public:
    MainFront(QWidget *parent = 0);
    ~MainFront();
    //void setBuyGoods(const int rowId, const int goodsID, const int goodsCount);
signals:
    //void rowStateChanged(QMap<int,RowInfo> rowInfo);
    public slots:
        void showRowState(int rowId, int restCnt);
        void showRowState(int rowId);
       // void showRowState(int rowId, bool isEnd);
        void showMsg(int rowId);
        void updateBuyInfoWedgit(const int rowId);
        //void updateBuyInfoWedgit();
        void test();
    private slots:
        void initVipTable();
        void showAllVIP();
        void lookupVIP();
        void registerVIP();
        void recharge();
        void deleteVIP();
        void reRegister();
        void initRowState();

        void swapRow();
        void showRowState();
        void showScore();
        void freeRow();
        void freeRow(int rowId);

        void bowlingBegin();
        void bowlingAddMoney();
        void callRepare();
        void lookupBookInfo();
        void showAllBookInfo();
        void showTodayBookInfo();
        void addCoachTeachInfo();
        void showCoachInfo();
        void showTeachInfo();

        void doGoodsSale();
        void checkGoodsStore();


        /*void showAllRow();
        void showAllBook();
        void showAllGoods();*/
private:
    QMap<int,RowInfo> rowInfo;
    QSqlTableModel *model;
    QSqlTableModel *coachModel;
    QVector<QString> itemText;
    QVector<QString> goodsItemText;
    QVector<QString> buyItemText;
    int initDispRowStateItem();
    void initGoodsStoreTable();
    void initBuyInfoWedgit();

    enum {propertyCount=7, goodsInfoProperty=5, buyInfoProperty=3, buyInfoRowSizeOne=64};
    Ui::MainFrontAdminUI ui;
    VipLookup vipLookup;
    VipRegister vipRegister;
    VipRecharge vipRecharge;
    ChangeRow changeRow;
    FrontCheckBook checkBook;
    AddTeachInfo addTeachInfo;
    TeachInfo teachInfo;
    GoodsSale goodsSale;
    Login login;
    //ScoreInformation scoreInformation;
    FrontServer *server;
    FrontTcpClient *client;
    FrontTcpClient *client2;

};

#endif

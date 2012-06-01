#include "mainFront.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QModelIndex>
#include <QMessageBox>
#include <QLocale>
#include <QDebug>
#include <QtSql>
#include <QTime>
#include <QInputDialog>

MainFront::MainFront(QWidget *parent /* = 0 */) : QWidget (parent)
{
    //ui.mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    QFile file("server_listen.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

     QTextStream in(&file);
     int port;
     if (!in.atEnd())
     {
        in >> port;
     }

    ui.setupUi(this);

    model = new QSqlTableModel;
    model->setTable("vip");
    coachModel = new QSqlTableModel;
    coachModel->setTable("coach");

    initRowState();
    //showRowState();
    server = new FrontServer;
    client = new  FrontTcpClient;
    client2 = new  FrontTcpClient;

    if (!server->listen(QHostAddress::Any, port))
    {
        QMessageBox::critical(NULL, "错误", "\n\n\n监听端口错误\n\n\n");
        return;
    }

    QObject::connect(server, SIGNAL(scoreChanged(int)), this, SLOT(showRowState(int)));
    QObject::connect(server, SIGNAL(endOne(int, int)), this, SLOT(showRowState(int, int)));
    //QObject::connect(server, SIGNAL(callService(int)), this, SLOT(showMsg(int)));
    QObject::connect(ui.pushButtonCheckScore, SIGNAL(clicked()), this, SLOT(showScore()));
    QObject::connect(ui.pushButtonShow, SIGNAL(clicked()), this, SLOT(showRowState()));
    QObject::connect(ui.pushButtonChangeRow, SIGNAL(clicked()), this, SLOT(swapRow()));
    QObject::connect(ui.pushButtonBowlingBegin, SIGNAL(clicked()), this, SLOT(bowlingBegin()));
    QObject::connect(ui.pushButtonAddMoney, SIGNAL(clicked()), this, SLOT(bowlingAddMoney()));
    QObject::connect(ui.pushButtonOption, SIGNAL(clicked()), this, SLOT(callRepare()));
    QObject::connect(ui.freeRowButton, SIGNAL(clicked()), this, SLOT(freeRow()));

    initVipTable();
    QObject::connect(ui.pushButtonShowAllVip, SIGNAL(clicked()), this, SLOT(showAllVIP()));
    QObject::connect(ui.pushButtonLookupVipInfo, SIGNAL(clicked()), this, SLOT(lookupVIP()));
    QObject::connect(ui.pushButtonRegister, SIGNAL(clicked()), this, SLOT(registerVIP()));
    QObject::connect(ui.pushButtonRecharge, SIGNAL(clicked()), this, SLOT(recharge()));
    QObject::connect(ui.pushButtonLost, SIGNAL(clicked()), this, SLOT(deleteVIP()));
    QObject::connect(ui.pushButtonReRegister, SIGNAL(clicked()), this, SLOT(reRegister()));

    checkBook.model->removeColumn(0);
    checkBook.model->setHeaderData(0, Qt::Horizontal, tr("会员编号"));
    checkBook.model->setHeaderData(1, Qt::Horizontal, tr("预约时间"));
    checkBook.model->setHeaderData(2, Qt::Horizontal, tr("预约球道"));
    QObject::connect(ui.pushButtonLookupBook, SIGNAL(clicked()), this, SLOT(lookupBookInfo()));
    QObject::connect(ui.pushButtonShowAllBookInfo, SIGNAL(clicked()), this, SLOT(showAllBookInfo()));
    QObject::connect(ui.pushButtonShowTodayBook, SIGNAL(clicked()), this, SLOT(showTodayBookInfo()));

    showCoachInfo();
    QObject::connect(ui.pushButtonAdd, SIGNAL(clicked()), this, SLOT(addCoachTeachInfo()));
    QObject::connect(ui.pushButtonLookupTeachInfo, SIGNAL(clicked()), this, SLOT(showTeachInfo()));
    //QObject::connect(ui.pushButtonLookupTeachInfo, SIGNAL(clicked()), &teachInfo, SLOT(showTeachInfo()));

    initGoodsStoreTable();
    initBuyInfoWedgit();
    QObject::connect(ui.doGoodsSaleButton, SIGNAL(clicked()), this, SLOT(doGoodsSale()));
    QObject::connect(ui.viewGoodsButton, SIGNAL(clicked()), this, SLOT(checkGoodsStore()));
    //test
    //rowInfo[1].buyGoodsId.push_back(1);
    //rowInfo[1].buyGoodsCount.push_back(6);

   // updateBuyInfoWedgit();
    //QObject::connect(ui.applyCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateBuyInfoWedgit()));
    QObject::connect(server, SIGNAL(buyGoodsChanged(int)), this, SLOT(updateBuyInfoWedgit(int)));

}

MainFront::~MainFront()
{
    delete model;
    for (int i=0; i<itemText[i].size(); i++)
    {
        //delete item[i];
        itemText[i].clear();
    }
    //item.clear();
    itemText.clear();
}

void MainFront::initRowState()
{
    QSqlQuery query;
    query.clear();
    query.prepare("SELECT * FROM row ORDER BY row_id");
    query.exec();
    int rowIdNo = query.record().indexOf("row_id");
    int rowStateNo = query.record().indexOf("row_state");
    int rowType = query.record().indexOf("row_type");

    while(query.next())
    {
        int id = query.value(rowIdNo).toInt();
        rowInfo[id].state = query.value(rowStateNo).toString();
        rowInfo[id].type = query.value(rowType).toString();
        rowInfo[id].buyGoodsInfo.goodsTypeSize = 0;
        rowInfo[id].totalPlayerCount = 0;
        rowInfo[id].currentPlayerNo = 0;
        rowInfo[id].useType = dataTransform::NO_USE;
        rowInfo[id].restCount = 0;
        rowInfo[id].restTime = "";

        changeRow.setRow(id);
        addTeachInfo.setRow(id);
       // scoreInformation.setRowId(id);

        rowInfo[id].writeInfo(id);
    }
    //scoreInformation.initTableWidget();
    // init the QTableWidget Items
    //item.resize(propertyCount*rowInfo.size());
    itemText.resize(propertyCount*rowInfo.size());
    ui.tableWidgetRowInfo->setColumnCount(propertyCount);
    ui.tableWidgetRowInfo->setRowCount(rowInfo.size());
    RowInfo tempRowInfo;
    QMapIterator<int, RowInfo> p(rowInfo);
    for (int i=0; i<rowInfo.size(); i++)
    {
        if (p.hasNext())
        {
            p.next();
            for (size_t j=0; j<propertyCount; j++)
            {
                tempRowInfo = p.value();
                switch(j)
                {
                case 0:
                    itemText[i*propertyCount+j].setNum(p.key());
                    break;
                case 1:
                    itemText[i*propertyCount+j] = tempRowInfo.state;
                    break;
                case 2:
                    itemText[i*propertyCount+j] = tempRowInfo.type;
                    break;
                default:
                    break;
                }
                ui.tableWidgetRowInfo->setItem(i, j, new QTableWidgetItem(itemText[i*propertyCount+j]));
                ui.tableWidgetRowInfo->item(i,j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsTristate | Qt::ItemIsSelectable);
                ui.tableWidgetRowInfo->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

int MainFront::initDispRowStateItem()
{
    // init the QTableWidget Items
    RowInfo tempRowInfo, test;
    QMapIterator<int, RowInfo> p(rowInfo);
    int dispRow=0;
    int i=0;
    for (i=0; i<rowInfo.size(); i++)
    {
        if (p.hasNext())
        {
            p.next();
            //rowInfo[p.key()].readInfo(p.key());
            if (rowInfo[p.key()].state==ui.comboBoxState->currentText()
                || rowInfo[p.key()].type==ui.comboBoxState->currentText()
                || "所有球道"==ui.comboBoxState->currentText())
            {

                for (size_t j=0; j<propertyCount; j++)
                {
                    tempRowInfo = p.value();
                    switch(j)
                    {
                    case 0:
                        itemText[dispRow*propertyCount+j].setNum(p.key());
                        break;
                    case 1:
                        itemText[dispRow*propertyCount+j] = tempRowInfo.state;
                        break;
                    case 2:
                        itemText[dispRow*propertyCount+j] = tempRowInfo.type;
                        break;
                    case 3:

                        if (tempRowInfo.state=="占用" && tempRowInfo.useType==dataTransform::IS_VIP)
                            itemText[dispRow*propertyCount+j] =  "会员顾客";
                        else if (tempRowInfo.state=="占用" && tempRowInfo.useType==dataTransform::NOT_VIP)
                            itemText[dispRow*propertyCount+j] = "普通顾客";
                        else
                            itemText[dispRow*propertyCount+j] = "";
                        break;
                    case 4:
                        itemText[dispRow*propertyCount+j] = tempRowInfo.vipId;
                        break;
                    case 5:
                        itemText[dispRow*propertyCount+j] = tempRowInfo.timeBegin;
                        break;
                    case 6:
                        itemText[dispRow*propertyCount+j].setNum(tempRowInfo.restCount);
                        break;
                    default:
                        break;
                    }
                }
                dispRow++;
            }
        }
        else
        {
            break;
        }
    }
    if (rowInfo.size()>dispRow)
    {
        for (int j=dispRow; j<rowInfo.size(); j++)
            for (size_t k=0; k<propertyCount; k++)
                itemText[j*propertyCount+k].clear();
    }
    return dispRow;
}

void MainFront::showRowState()
{
    //QMessageBox::critical(0, "收到信号", "\n显示球道信息\n");
    int dispRow = initDispRowStateItem();
    for (int i=0; i<dispRow; i++)
    {
        for (int j=0; j<propertyCount; j++)
        {
            ui.tableWidgetRowInfo->item(i,j)->setText(itemText[i*propertyCount+j]);
            //ui.tableWidgetRowInfo->setItem(i,j,item[i*propertyCount+j]);
        }
    }
    for (int i=dispRow; i<ui.tableWidgetRowInfo->rowCount(); i++)
    {
        for (int j=0; j<propertyCount; j++)
        {
            ui.tableWidgetRowInfo->item(i,j)->setText("");
            //ui.tableWidgetRowInfo->setItem(i,j,item[i*propertyCount+j]);
        }
    }
    //emit rowStateChanged(rowInfo);
}

void MainFront::showRowState(int rowId, int restCnt)
{
    for (int i=0; i<ui.tableWidgetRowInfo->rowCount(); i++)
    {
        if (ui.tableWidgetRowInfo->item(i,0)->text().toInt()==rowId)
        {
            QString rest;
            rest.setNum(restCnt);
            ui.tableWidgetRowInfo->item(i,propertyCount-1)->setText(rest);
        }
    }
/*
    if (!rowInfo[rowId].readInfo(rowId))
        QMessageBox::critical(0, "收到信号", "\n读取文件错误，收到得分改变信号，球道状态改变\n");
    else
        showRowState();
*/
}

void MainFront::showRowState(int rowId)
{
    if (!rowInfo[rowId].readInfo(rowId))
        QMessageBox::critical(0, "收到信号", "\n读取文件错误，收到得分改变信号，球道状态改变\n");
}


void MainFront::freeRow()
{
    int ret = QMessageBox::question(NULL, "强制空闲", "\n确认修改球道状态为空闲状态?\n", QMessageBox::Ok | QMessageBox::Cancel);
    if (ret!=1024)
        return;
    int id = ui.tableWidgetRowInfo->item(ui.tableWidgetRowInfo->currentRow(), 0)->text().toInt();
    rowInfo[id].restCount = 0;
    rowInfo[id].currentPlayerNo = 0;
    rowInfo[id].buyGoodsInfo.goodsCount.clear();
    rowInfo[id].buyGoodsInfo.goodsId.clear();
    rowInfo[id].buyGoodsInfo.goodsTypeSize = 0;
    rowInfo[id].totalPlayerCount = 0;
    rowInfo[id].restTime.clear();
    rowInfo[id].timeBegin.clear();
    rowInfo[id].vipId.clear();
    rowInfo[id].scoreInfo.clear();
    rowInfo[id].writeInfo(id);
    client->connectToServer(id, dataTransform::ANS_DISMISS, 0);
    ui.tableWidgetRowInfo->item(ui.tableWidgetRowInfo->currentRow(),1)->setText("空闲");
    for (int i=3; i<propertyCount; i++)
        ui.tableWidgetRowInfo->item(ui.tableWidgetRowInfo->currentRow(),i)->setText("");
}

void MainFront::freeRow(int rowId)
{
    int id = rowId;
    rowInfo[id].restCount = 0;
    rowInfo[id].currentPlayerNo = 0;
    rowInfo[id].buyGoodsInfo.goodsCount.clear();
    rowInfo[id].buyGoodsInfo.goodsId.clear();
    rowInfo[id].buyGoodsInfo.goodsTypeSize = 0;
    rowInfo[id].totalPlayerCount = 0;
    rowInfo[id].restTime.clear();
    rowInfo[id].timeBegin.clear();
    rowInfo[id].vipId.clear();
    rowInfo[id].scoreInfo.clear();
    rowInfo[id].writeInfo(id);
    client->connectToServer(id, dataTransform::ANS_DISMISS, 0);
    ui.tableWidgetRowInfo->item(ui.tableWidgetRowInfo->currentRow(),1)->setText("空闲");
    for (int i=3; i<propertyCount; i++)
        ui.tableWidgetRowInfo->item(ui.tableWidgetRowInfo->currentRow(),i)->setText("");

}


void MainFront::showScore()
{
    //scoreInformation.setRowInfo(rowInfo);
    //scoreInformation.showScore();
    //scoreInformation.show();
    QString rid = ui.tableWidgetRowInfo->item(ui.tableWidgetRowInfo->currentRow(),0)->text();
    //QList<QString> score;
    QString str;
    RowInfo tempInfo = rowInfo[rid.toInt()];
    for (int i=0; i<tempInfo.totalPlayerCount && i<tempInfo.scoreInfo.size(); i++)
    {
        str.append(QString('A' + i).toLocal8Bit());
        str.append("\n");
        int turn = rowInfo[rid.toInt()].scoreInfo[0].turn;
        for (int j=0; j<=turn && turn<dataTransform::SCORE_SIZE; j++)
        {
            int count_blank = 8 - tempInfo.scoreInfo[i].str[j].length();
            str.append(tempInfo.scoreInfo[i].str[j]);
            for (int k=0; k<count_blank; k++)
            {
                str.append(" ");
            }
        }
        //for (int j=turn+1; j<dataTransform::SCORE_SIZE; j++)
        //    str.append("        ");
        str.append("\n");
        for (int j=0; j<=turn && turn<dataTransform::SCORE_SIZE; j++)
        {
            QString score;
            score.setNum(tempInfo.scoreInfo[i].score[j]);
            int count_blank = 8 - score.length();
            str.append(score);
            for (int k=0; k<count_blank; k++)
            {
                str.append(" ");
            }
        }
        //for (int j=turn+1; j<dataTransform::SCORE_SIZE; j++)
        //    str.append("        ");
        str.append("\n\n");
    }
    QMessageBox msgBox;
    msgBox.setWindowTitle("查看分数");
    msgBox.setText(rid + " 号球道");
    msgBox.setInformativeText(str);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}


void MainFront::bowlingBegin()
{
    QString rowId;
    QMessageBox msgBox;
    if (ui.tableWidgetRowInfo->currentRow()==-1)
        QMessageBox::critical(NULL,"错误", "请选中要登记的球道");
    else
    {
        int currentRow = ui.tableWidgetRowInfo->currentRow();
        rowId = ui.tableWidgetRowInfo->item(currentRow,0)->text();

        login.setRowID(rowId);
        //QMessageBox::critical(0, "登记球道", "球道号: " + login.rowID);
        int ret  = login.exec();
        switch (ret)
        {
        case 1:
            if (!login.isSuccess)
            {
                QMessageBox::critical(NULL, "错误", "\n登记错误，请输入数字!\n");
                break;
            }
            rowInfo[rowId.toInt()].state = "占用";
            rowInfo[rowId.toInt()].restCount = login.rest.toInt();

            itemText[currentRow*propertyCount+1] = "占用";
           // item[currentRow*propertyCount+1]->setText(itemText[currentRow*propertyCount+1]);
            ui.tableWidgetRowInfo->item(currentRow,1)->setText(itemText[currentRow*propertyCount+1]);
            //item[currentRow*propertyCount+1]->setTextAlignment(Qt::AlignCenter);
            //ui.tableWidgetRowInfo->setItem(currentRow, 1, item[currentRow*propertyCount+1]);
            if (login.customerType==Login::NOT_VIP)
            {
                itemText[currentRow*propertyCount+3] = "普通顾客";
                itemText[currentRow*propertyCount+4].clear();
                rowInfo[rowId.toInt()].useType = dataTransform::NOT_VIP;
            }
            else
            {
                itemText[currentRow*propertyCount+3] = "会员顾客";
                itemText[currentRow*propertyCount+4].setNum(login.vipId);
                rowInfo[rowId.toInt()].vipId = itemText[currentRow*propertyCount+4];

                rowInfo[rowId.toInt()].useType = dataTransform::IS_VIP;
                //QMessageBox::critical(0, "VIP号" , "\n\n" + rowInfo[rowId.toInt()].vipId + "\n\n");
            }
            itemText[currentRow*propertyCount+5] = QTime::currentTime().toString("hh:mm");
            rowInfo[rowId.toInt()].timeBegin = itemText[currentRow*propertyCount+5];
            if (login.playType==Login::IS_COUNT && login.rest.toInt()>0)
            {
                itemText[currentRow*propertyCount+6] = login.rest;
                rowInfo[rowId.toInt()].restCount = login.rest.toInt();
                rowInfo[rowId.toInt()].restTime.clear();
            }
            else if (login.playType==Login::IS_TIME && login.rest.toDouble()>0)
            {
                itemText[currentRow*propertyCount+6] = login.rest;
                rowInfo[rowId.toInt()].restTime = login.rest;
                rowInfo[rowId.toInt()].restCount = 0;
            }
            else
            {
                itemText[currentRow*propertyCount+6].clear();
                rowInfo[rowId.toInt()].restTime.clear();
                rowInfo[rowId.toInt()].restCount = 0;
            }

            for (int i=3; i<=6; i++)
            {
                //QMessageBox::critical(0, "返回值" , "\n\n" + res +"\n\n");
                //item[currentRow*propertyCount+i]->setText(itemText[currentRow*propertyCount+i]);
                ui.tableWidgetRowInfo->item(currentRow, i)->setText(itemText[currentRow*propertyCount+i]);
                //item[currentRow*propertyCount+i]->setTextAlignment(Qt::AlignCenter);
                //ui.tableWidgetRowInfo->removeCellWidget(currentRow, 1);
                //ui.tableWidgetRowInfo->setItem(currentRow, i, item[currentRow*propertyCount+i]);
            }

            client->connectToServer(rowId.toInt(), dataTransform::ANS_YES_YOU_CAN_BEGIN, rowInfo[rowId.toInt()].restCount);
            break;
        case 0:
            break;
        default:
            break;
        }
        rowInfo[rowId.toInt()].writeInfo(rowId.toInt());
        //showRowState();
    }
}

void MainFront::bowlingAddMoney()
{
    if (ui.tableWidgetRowInfo->currentRow()==-1)
        QMessageBox::critical(NULL,"错误", "请选中要续费的球道");
    bool ok;
    int add = QInputDialog::getInt(this, tr("续费"), tr("输入续费局数："), NULL, 0, 100, 1, &ok);
    if (ok)
    {
        int currentRow = ui.tableWidgetRowInfo->currentRow();
        int rowId = ui.tableWidgetRowInfo->item(currentRow,0)->text().toInt();
        rowInfo[rowId].restCount += add;
        rowInfo[rowId].writeInfo(rowId);
        int restCnt = rowInfo[rowId].restCount;
        QString restS;
        restS.setNum(restCnt);
        client->connectToServer(rowId, dataTransform::ANS_AFTER_ADD_MONEY, restCnt);
        ui.tableWidgetRowInfo->item(currentRow, propertyCount-1)->setText(restS);
    }
}

void MainFront::swapRow()
{
    int res;
    res = changeRow.exec();
    //QMessageBox::critical(0, "取消", "返回值 " + ress);
    if (res==0)
        return;
    RowInfo temp = rowInfo[changeRow.prevRowId] ;
/*
    temp.state = rowInfo[changeRow.prevRowId].state;
    rowInfo[changeRow.prevRowId].state = rowInfo[changeRow.afterRowId].state;
    rowInfo[changeRow.afterRowId].state = temp.state;
*/
    rowInfo[changeRow.prevRowId] = rowInfo[changeRow.afterRowId];
    rowInfo[changeRow.afterRowId] = temp;

    if (rowInfo[changeRow.prevRowId].type != rowInfo[changeRow.afterRowId].type)
    {
        QString type = rowInfo[changeRow.prevRowId].type;
        rowInfo[changeRow.prevRowId].type = rowInfo[changeRow.afterRowId].type;
        rowInfo[changeRow.afterRowId].type = type;
        //QMessageBox::critical(0, "更换", "更换");
    }

    rowInfo[changeRow.afterRowId].writeInfo(changeRow.afterRowId);
//    client->connectToServer(changeRow.prevRowId, dataTransform::ANS_YOU_CAN_EXCHANGE_ROW, rowInfo[changeRow.prevRowId]);
    client2->connectToServer(changeRow.afterRowId, dataTransform::ANS_YOU_CAN_EXCHANGE_ROW, rowInfo[changeRow.afterRowId]);
    client->connectToServer(changeRow.prevRowId, dataTransform::ANS_DISMISS, 0);
    freeRow(changeRow.prevRowId);
    rowInfo[changeRow.prevRowId].writeInfo(changeRow.prevRowId);
    showRowState();
}

void MainFront::callRepare()
{
    QMessageBox msgBox;
    if (ui.tableWidgetRowInfo->currentRow()==-1)
        QMessageBox::critical(NULL,"错误", "请选中要报修的球道");
    else
    {
        QString rowId(ui.tableWidgetRowInfo->item(ui.tableWidgetRowInfo->currentRow(),0)->text());
        //QMessageBox::critical(NULL,"rowId", rowId);
        msgBox.setText("报修球道号: " + rowId);
        msgBox.setInformativeText("Yes or No ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        QSqlQuery query("UPDATE row SET row_state='维修' where row_id=" + rowId);
        switch (ret)
        {
        case QMessageBox::Yes:
            rowInfo[rowId.toInt()].state = "维修";
            if (query.exec())
            {
                QMessageBox::information(NULL, "正确",  "报修成功!", QMessageBox::Ok, QMessageBox::Ok);
                itemText[ui.tableWidgetRowInfo->currentRow()*propertyCount+1] = "维修";
                //item[ui.tableWidgetRowInfo->currentRow()*propertyCount+1]->setText(itemText[ui.tableWidgetRowInfo->currentRow()*propertyCount+1]);
                ui.tableWidgetRowInfo->item(ui.tableWidgetRowInfo->currentRow(),1)->setText(itemText[ui.tableWidgetRowInfo->currentRow()*propertyCount+1]);

                //item[ui.tableWidgetRowInfo->currentRow()*propertyCount+1]->setTextAlignment(Qt::AlignCenter);
                //ui.tableWidgetRowInfo->removeCellWidget(ui.tableWidgetRowInfo->currentRow(), 1);
                //ui.tableWidgetRowInfo->setItem(ui.tableWidgetRowInfo->currentRow(), 1, item[ui.tableWidgetRowInfo->currentRow()*propertyCount+1]);
            }
            else
            {
                QMessageBox::information(NULL, "错误",  "报修失败!", QMessageBox::Ok, QMessageBox::Ok);
            }
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }
        //showRowState();
    }
}

void MainFront::initVipTable()
{
    model->setHeaderData(0, Qt::Horizontal, tr("序号"));
    model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal, tr("性别"));
    model->setHeaderData(3, Qt::Horizontal, tr("身份证号"));
    model->setHeaderData(4, Qt::Horizontal, tr("电话"));
    model->setHeaderData(5, Qt::Horizontal, tr("注册日期"));
    model->setHeaderData(6, Qt::Horizontal, tr("优惠类型"));
    model->setHeaderData(7, Qt::Horizontal, tr("余额"));

}

void MainFront::showAllVIP()
{
    //model->setFilter("SELECT * FROM vip");
    initVipTable();
    if (model->select())
    {
        /*model->setHeaderData(0, Qt::Horizontal, tr("序号"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("性别"));
        model->setHeaderData(3, Qt::Horizontal, tr("身份证号"));
        model->setHeaderData(4, Qt::Horizontal, tr("电话"));
        model->setHeaderData(5, Qt::Horizontal, tr("注册日期"));
        model->setHeaderData(6, Qt::Horizontal, tr("优惠类型"));
        model->setHeaderData(7, Qt::Horizontal, tr("余额"));*/

        ui.tableViewVipInfo->setModel(model);
        ui.tableViewVipInfo->setColumnWidth(3, 160);
        //ui.tableViewVipInfo->setGridStyle(Qt::PenStyle);
        ui.tableViewVipInfo->show();
    }
}

void MainFront::lookupVIP()
{
    vipLookup.exec();
    //QSqlTableModel  *model = vipLookup.model;
    //model = vipLookup.model;
    if (vipLookup.model->select())
    {
        vipLookup.model->setHeaderData(0, Qt::Horizontal, tr("序号"));
        vipLookup.model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        vipLookup.model->setHeaderData(2, Qt::Horizontal, tr("性别"));
        vipLookup.model->setHeaderData(3, Qt::Horizontal, tr("身份证号"));
        vipLookup.model->setHeaderData(4, Qt::Horizontal, tr("电话"));
        vipLookup.model->setHeaderData(5, Qt::Horizontal, tr("注册日期"));
        vipLookup.model->setHeaderData(6, Qt::Horizontal, tr("优惠类型"));
        vipLookup.model->setHeaderData(7, Qt::Horizontal, tr("余额"));

        //QTableView *view = ui.tableViewVipInfo;
        ui.tableViewVipInfo->setModel(vipLookup.model);
        ui.tableViewVipInfo->setColumnWidth(3,160);
        ui.tableViewVipInfo->show();
        vipLookup.hide();
    }

}

void MainFront::registerVIP()
{
    vipRegister.exec();
    vipRegister.query.exec();
}

void MainFront::recharge()
{
    QModelIndex currIndex, headIndex;
    currIndex=ui.tableViewVipInfo->currentIndex();
    headIndex = ui.tableViewVipInfo->model()->index(currIndex.row(), 0);
//	sname=ui.tableViewVipInfo->model()->record(index.row()).value(1).toString();
    //QMessageBox::critical(0, "测试信号", headIndex.data().toString());
    vipRecharge.exec();
    QSqlQuery query;
    if (vipRecharge.money!="")
    {
        query.prepare("UPDATE vip SET vip_balance=vip_balance+" + vipRecharge.money + " where vip_id=" + headIndex.data().toString());
        if (query.exec())
        {
            query.prepare("SELECT vip_name, vip_balance FROM vip WHERE vip_id=" + headIndex.data().toString());
            query.exec();
            query.next();
            //QMessageBox::Information(NULL, "正确", "充值成功", QMessageBox::Ok, QMessageBox::Ok);
            QMessageBox::information(NULL, "正确", "充值成功\n\n" + query.value(0).toString() + " 余额:\t" + query.value(1).toString(),
                QMessageBox::Ok, QMessageBox::Ok);
        }
        else
            QMessageBox::critical(NULL,"错误","充值失败!\n\n" + query.lastError().text());
    }
}

void MainFront::deleteVIP()
{
    QModelIndex currIndex, headIndex;
    currIndex=ui.tableViewVipInfo->currentIndex();
    headIndex = ui.tableViewVipInfo->model()->index(currIndex.row(), 0);
    QString msg = "会员姓名:\t" + ui.tableViewVipInfo->model()->index(currIndex.row(), 1).data().toString() + '\n'
        + "会员编号:\t" + headIndex.data().toString() + '\n'
        + "身份证号:\t" + ui.tableViewVipInfo->model()->index(currIndex.row(), 3).data().toString();
    QSqlQuery query;

    query.prepare("DELETE FROM vip WHERE vip_id=" + headIndex.data().toString());
    //QMessageBox::information(NULL, "Are you sure?", "Yes or No?",
    //	QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    /*QMessageBox msgBox;
    msgBox.setWindowTitle("警告");
    msgBox.setText("删除\n\n" + msg);
    msgBox.setInformativeText("Yes or No ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);*/
    //int ret = msgBox.exec();
    int ret = QMessageBox::warning(this, tr("删除确认"), "删除\n\n" + msg + "\n\n确认?",
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        query.exec();
        showAllVIP();
        break;
    case QMessageBox::No:
        break;
    default:
        break;
    }
}

void MainFront::reRegister()
{
    QModelIndex currIndex, headIndex;
    currIndex=ui.tableViewVipInfo->currentIndex();
    headIndex = ui.tableViewVipInfo->model()->index(currIndex.row(), 0);

    QSqlQuery query, queryDelete, querySelect;

    query.prepare("INSERT INTO vip(vip_name, vip_sex, vip_cardid, vip_phone, vip_login_date, vip_type, vip_balance) "
        "VALUES (:vip_name, :vip_sex, :vip_cardid, :vip_phone, :vip_login_date, :vip_type, :vip_balance)");

    QString id(ui.tableViewVipInfo->model()->index(currIndex.row(), 0).data().toString());
    QString name(ui.tableViewVipInfo->model()->index(currIndex.row(), 1).data().toString());
    QString sex(ui.tableViewVipInfo->model()->index(currIndex.row(), 2).data().toString());
    QString cardId(ui.tableViewVipInfo->model()->index(currIndex.row(), 3).data().toString());
    QString phone(ui.tableViewVipInfo->model()->index(currIndex.row(), 4).data().toString());
    QString loginDate(ui.tableViewVipInfo->model()->index(currIndex.row(), 5).data().toString());
    QString type(ui.tableViewVipInfo->model()->index(currIndex.row(), 6).data().toString());
    QString money(ui.tableViewVipInfo->model()->index(currIndex.row(), 7).data().toString());

    query.bindValue(":vip_name", name);
    query.bindValue(":vip_sex", sex);
    query.bindValue(":vip_cardid", cardId);
    query.bindValue(":vip_phone", phone);
    query.bindValue(":vip_login_date", loginDate);
    query.bindValue(":vip_type", type.toInt());
    query.bindValue(":vip_balance", money.toDouble());

    queryDelete.prepare("DELETE FROM vip WHERE vip_id=" + id);
    if (!queryDelete.exec())
    {
        QMessageBox::critical(NULL,"错误", "请选择需要挂失的会员,错误信息:\n\n" + queryDelete.lastError().text());
        return;
    }
    if (!query.exec())
    {
        QMessageBox::critical(NULL,"错误", "更新失败,错误信息:\n\n" + query.lastError().text());
        return;
    }

    QString updateId;
    querySelect.prepare("SELECT vip_id FROM vip WHERE vip_name=\'" + name + "\' AND " + "vip_cardid=\'" + cardId + "\'");
    if (!querySelect.exec())
    {
        QMessageBox::critical(NULL,"错误", "更新失败,错误信息:\n\n" + querySelect.lastError().text());
        return;
    }
    querySelect.next();
    id = querySelect.value(0).toString();
    QString msg = "挂失成功!\n\n会员姓名: " + name + "\n会员编号: " + id + "\n身份证号: " + cardId + "\n";

    QMessageBox::information(NULL, "更新成功!",  msg, QMessageBox::Ok, QMessageBox::Ok);

    showAllVIP();
}

void MainFront::lookupBookInfo()
{
    //ui.tableViewBookFront->hide();
    checkBook.exec();
    checkBook.model->select();
    ui.tableViewBookFront->setModel(checkBook.model);
    ui.tableViewBookFront->show();
}

void MainFront::showAllBookInfo()
{
    //checkBook.exec();
    ui.tableViewBookFront->hide();
    checkBook.model->setFilter(NULL);
    checkBook.model->select();
    ui.tableViewBookFront->setModel(checkBook.model);
    ui.tableViewBookFront->show();
}

void MainFront::showTodayBookInfo()
{
    ui.tableViewBookFront->hide();
    QDate today = QDate::currentDate();
    QDate tomorrow = today.addDays(1);
    QString filter("book_date >= '" + today.toString("yyyy-MM-dd h:m:s") + "' AND book_date <= '" + tomorrow.toString("yyyy-MM-dd h:m:s") + "';");
    checkBook.model->setFilter(filter);
    checkBook.model->select();
    ui.tableViewBookFront->setModel(checkBook.model);
    ui.tableViewBookFront->show();
}

void MainFront::addCoachTeachInfo()
{
    QModelIndex currIndex, headIndex;
    currIndex=ui.tableViewCoachInfo->currentIndex();
    headIndex = ui.tableViewCoachInfo->model()->index(currIndex.row(), 0);
    QString coachName = headIndex.data().toString();
    addTeachInfo.setCoachInfo(coachName);
    addTeachInfo.exec();
}

void MainFront::showCoachInfo()
{
    if (coachModel->select())
    {
        coachModel->removeColumn(0);
        coachModel->setHeaderData(0, Qt::Horizontal, tr("姓名"));
        coachModel->setHeaderData(1, Qt::Horizontal, tr("性别"));
        coachModel->setHeaderData(2, Qt::Horizontal, tr("电话"));

        ui.tableViewCoachInfo->setModel(coachModel);
        ui.tableViewCoachInfo->show();
    }
}

void MainFront::showTeachInfo()
{
    QModelIndex currIndex, headIndex;
    currIndex=ui.tableViewCoachInfo->currentIndex();
    headIndex = ui.tableViewCoachInfo->model()->index(currIndex.row(), 0);
    QString coachName = headIndex.data().toString();
    teachInfo.setCoach(coachName);
    teachInfo.showTeachInfo();
    teachInfo.exec();
}

void MainFront::initGoodsStoreTable()
{
    QSqlQuery query;
    query.prepare("SELECT * from goods;");
    query.exec();
    goodsItemText.clear();
    while (query.next())
    {
        for (int i=0; i<goodsInfoProperty; i++)
        {
            goodsItemText.push_back(query.value(i).toString());
        }
    }
    //goodsItem.resize(goodsItemText.size());
    int rowSize = goodsItemText.size()/goodsInfoProperty;
    ui.tableWidgetGoodsSaleInfo->setColumnCount(goodsInfoProperty);
    ui.tableWidgetGoodsSaleInfo->setRowCount(rowSize);
    for (int i=0; i<rowSize; i++)
    {
        for (int j=0; j<goodsInfoProperty; j++)
        {
            ui.tableWidgetGoodsSaleInfo->setItem(i, j, new QTableWidgetItem(goodsItemText[i*goodsInfoProperty+j]));
            ui.tableWidgetGoodsSaleInfo->item(i,j)->setTextAlignment(Qt::AlignCenter);
            ui.tableWidgetGoodsSaleInfo->item(i,j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsTristate);
        }
    }
}

void MainFront::checkGoodsStore()
{
    QString currentChose = ui.goodsCombox->currentText();
    int rowSize = ui.tableWidgetGoodsSaleInfo->rowCount();
    QSqlQuery query;
    if (currentChose=="全部")
        query.prepare("SELECT * from goods;");
    else
        query.prepare("SELECT * from goods WHERE goods_remark=\'" + currentChose + "\'");
    query.exec();
    goodsItemText.clear();
    while (query.next())
    {
        for (int i=0; i<goodsInfoProperty; i++)
        {
            goodsItemText.push_back(query.value(i).toString());
        }
    }
    int dispRow = goodsItemText.size()/goodsInfoProperty;
    for (int i=0; i<dispRow; i++)
    {
        for (int j=0; j<goodsInfoProperty; j++)
        {
            //goodsItemText[dispRowNo*rowSize+j] = ui.tableWidgetGoodsSaleInfo->item(i,j)->text();
            ui.tableWidgetGoodsSaleInfo->item(i, j)->setText(goodsItemText[i*goodsInfoProperty+j]);
        }
    }
    for (int i=dispRow; i<rowSize; i++)
    {
        for (int j=0; j<goodsInfoProperty; j++)
        {
            ui.tableWidgetGoodsSaleInfo->item(i, j)->setText("");
        }
    }
}

void MainFront::initBuyInfoWedgit()
{
    ui.buyInfotableWidget->setColumnCount(buyInfoProperty);
    ui.buyInfotableWidget->setRowCount(rowInfo.size());
    for (int i=0; i<rowInfo.size(); i++)
    {
        for (int j=0; j<buyInfoProperty; j++)
        {
            ui.buyInfotableWidget->setItem(i, j, new QTableWidgetItem);
            ui.buyInfotableWidget->item(i,j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsTristate | Qt::ItemIsSelectable);
            ui.buyInfotableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void MainFront::updateBuyInfoWedgit(const int rowId)
{
    //qDebug() << rowId << " 买商品了";
    if (rowId!=-1)
        rowInfo[rowId].readInfo(rowId);
    QMapIterator<int, RowInfo> p(rowInfo);
    int buySize;
        //int buyRowNo = 0, buyColNo = 0;
    buyItemText.clear();

    while (p.hasNext())
    {
        p.next();
        //buySize = rowInfo[p.key()].buyGoodsId.size();
        //buySize = rowInfo[p.key()].buyGoodsInfo.goodsTypeSize;
        buySize = rowInfo[p.key()].buyGoodsInfo.goodsId.size() < rowInfo[p.key()].buyGoodsInfo.goodsCount.size()
                  ? rowInfo[p.key()].buyGoodsInfo.goodsId.size() : rowInfo[p.key()].buyGoodsInfo.goodsCount.size();
        if (buySize>0 && (ui.applyCombox->currentText()==rowInfo[p.key()].type || ui.applyCombox->currentText()=="全部"))
        {
            //qDebug() << buySize << "进来了";
            QString temp;
            temp.setNum(p.key());
            buyItemText.push_back(temp);
            buyItemText.push_back(rowInfo[p.key()].type);
            buyItemText.push_back("待处理");
        }
    }

//    buyItem.resize(buyItemText.size());
    int rowCount=buyItemText.size()/buyInfoProperty;
    //qDebug() << "买的人数:" << rowCount;
    for (int i=0; i<rowCount; i++)
    {
        for (int j=0; j<buyInfoProperty; j++)
        {
            ui.buyInfotableWidget->item(i,j)->setText(buyItemText[i*buyInfoProperty+j]);
        }
    }
    for (int i=rowCount; i<ui.buyInfotableWidget->rowCount(); i++)
    {
        for (int j=0; j<buyInfoProperty; j++)
            ui.buyInfotableWidget->item(i,j)->setText("");
    }
}

void MainFront::doGoodsSale()
{
    if (ui.buyInfotableWidget->currentRow()==-1)
    {
        QMessageBox::critical(NULL, "错误", "请选中需要处理的球道");
        return;
    }
    QString rowId = ui.buyInfotableWidget->item(ui.buyInfotableWidget->currentRow(), 0)->text();
    //rowInfo[tempId.toInt()].buyGoodsId.push_back(1);
    //rowInfo[tempId.toInt()].buyGoodsCount.push_back(6);
    //QString test;
    //test.setNum(rowInfo[tempId.toInt()].buyGoodsId.size());
    //QMessageBox::critical(0,"之前", "购买个数"+test);
    goodsSale.setBuyInfo(rowId.toInt(), rowInfo);
    goodsSale.prepareShow();
    int res = goodsSale.exec();
    if (res==1)
    {
        /*rowInfo[rowId.toInt()].buyGoodsCount.clear();
        rowInfo[rowId.toInt()].buyGoodsId.clear();*/
        rowInfo[rowId.toInt()].buyGoodsInfo.goodsTypeSize = 0;
        rowInfo[rowId.toInt()].buyGoodsInfo.goodsId.clear();
        rowInfo[rowId.toInt()].buyGoodsInfo.goodsCount.clear();
    }
    updateBuyInfoWedgit(-1);
    //QString ress;
    //ress.setNum(res);
    //QMessageBox::critical(0, "测试", "返回值 " + ress);
}

void MainFront::showMsg(int rowId)
{
    QString temp;
    temp.setNum(rowId);
    QMessageBox::critical(0, "内部信号", "主类收到信号，显示球道号 " +temp + "\n\n");
}

void MainFront::test()
{
    //qDebug()<<"I am in";
}

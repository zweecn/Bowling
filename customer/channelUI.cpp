#include "channelUI.h"
#include <QDebug>
#include <QSqlQuery>

Channel::Channel(QWidget *parent):QWidget(parent),number(2)
{

}

void Channel::initChannelLayout()
{
    channelLayout = new QVBoxLayout(channelNumWidget);
    channelLayout->setSpacing(6);
    channelLayout->setContentsMargins(0, 0, 0, 0);
	QFont fnt;
	fnt.setPointSize(18);
	fnt.setWeight(QFont::Bold);
    for(int i=0;i<3;i++)
    {
        QWidget *tmpWidget=new QWidget(channelNumWidget);
        QHBoxLayout *tmpHorizontal = new QHBoxLayout();
        tmpHorizontal->setSpacing(6);
        QLabel *label_2 = new QLabel(tr(QString('A'+i).toLocal8Bit()),channelNumWidget);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
		label_2->setFont(fnt);

		QSpacerItem *horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		tmpHorizontal->addItem(horizontalSpacer_12);
        tmpHorizontal->addWidget(label_2);
        QSpacerItem *horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
        tmpHorizontal->addItem(horizontalSpacer_9);
        QVBoxLayout *verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        QLabel *label_3 = new QLabel(tr("01    02    03    04    05    06    07    08    09    10   "), channelNumWidget);
		
		label_3->setFont(fnt);
        verticalLayout_2->addWidget(label_3);
        QLabel *label_A = new QLabel(channelNumWidget);
		label_A->setFont(fnt);
        verticalLayout_2->addWidget(label_A);
        
        channelLayout->addWidget(tmpWidget);
        widgetList.append(tmpWidget);
        labelListA.append(label_A);
		QLabel *label_B = new QLabel(channelNumWidget);
		verticalLayout_2->addWidget(label_B);
		label_B->setFont(fnt);
		labelListB.append(label_B);
		
		tmpHorizontal->addLayout(verticalLayout_2);
		QSpacerItem *horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		tmpHorizontal->addItem(horizontalSpacer_13);
		tmpWidget->setLayout(tmpHorizontal);
    }
    channelNumWidget->setLayout(channelLayout);

}

void Channel::initConnection()
{
    connect(channelPushButton, SIGNAL(clicked()), this, SLOT(getPushButtonDown()));
    connect(foodPushButton, SIGNAL(clicked()), this, SLOT(getPushButtonDown()));
    connect(historyPushButton, SIGNAL(clicked()), this, SLOT(getPushButtonDown()));
    connect(callPushButton, SIGNAL(clicked()), this, SLOT(callService()));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(getChannelShow(int)));
	connect(okPushButton, SIGNAL(clicked()), this, SLOT(orderService()));
	connect(historyTableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(getHistoryShow(int, int)));
	connect(pushButton, SIGNAL(clicked()), this, SLOT(unableCombobox()));

	//connect(&tcpCtrl, SIGNAL(dataReceived(int)), this, SLOT(initRestCount(int)));
	//connect(&tcpCtrl, SIGNAL(dataReceived(RowInfo)), this, SLOT(intRowinfo(RowInfo)));
}

void Channel::initRestCount(int restCnt)
{
	restCount = restCnt;
    //qDebug() << "Client rest count" << restCount;
    if (restCount==dataTransform::ANS_CLEAR_SCORE)
    {
        for (int i = 0; i < 3; i++)
        {
            labelListA[i]->clear();
            labelListB[i]->clear();
        }
    }
    else if (restCount > 0)
    {
		comboBox->setEnabled(true);
		pushButton->setEnabled(true);
		if (comboBox->currentIndex() > restCount - 1)
		{
			comboBox->setCurrentIndex(restCount - 1);
		}
	}
}

void Channel::addRestCount(int restCnt)
{
    restCount = restCnt;
}

void Channel::intRowinfo(RowInfo info)
{
	int i, j, k;
	if (info.scoreInfo.size() > 0)
	{
		turn = info.scoreInfo[0].turn;
		playerNO = info.totalPlayerCount - 1;
		currentPlayer = info.currentPlayerNo;
		for (j = 0; j <= playerNO; j++)
		{
			for (i = 0; i < 10; i++)
			{
				score[i][j] = info.scoreInfo[j].score[i];
				str[i][j] = info.scoreInfo[j].str[i];
				for (k = 0; k < 4; k++)
				{
					bt[k][i][j] = info.scoreInfo[j].bt[k][i];
				}
			}
		}
	}
	comboBox->setCurrentIndex(playerNO);
	int count_blank;
	
	for (k = 0; k <= playerNO; k++)
	{
		QString s;
		for(i = 0; i <= turn; i++)
		{
			count_blank = 6 - str[i][k].length();
			s.append(str[i][k]);
			for (j = 0; j < count_blank; j++)
			{
				s.append(" ");
			}
		}
		labelListA[k]->setText(s);

		QString ss;
		QString tmp;
		
		for(i = 0; i <= turn; i++)
		{
			tmp.setNum(score[i][k]);
			count_blank = 6 - tmp.length();
			ss.append(tmp);
			for (j = 0; j < count_blank; j++)
			{
				ss.append(" ");
			}
		}
		labelListB[k]->setText(ss);
	}
	if (currentPlayer == playerNO)
	{		
		turn++;
	}
	currentPlayer = (currentPlayer + 1) % (playerNO + 1);
	showScore();
}

void Channel::getRowInfo(const int n, const int p)
{
	int i, j, k;
	
	rowInformation.totalPlayerCount = playerNO + 1;
	rowInformation.scoreInfo.resize(playerNO + 1);
	rowInformation.currentPlayerNo = p;
	for (j = 0; j <= playerNO; j++)
	{
		rowInformation.scoreInfo[j].turn = n;
		for (i = 0; i < 10; i++)
		{
			rowInformation.scoreInfo[j].score[i] = score[i][j];
			rowInformation.scoreInfo[j].str[i] = str[i][j];
			for (k = 0; k < 4; k++)
			{
				rowInformation.scoreInfo[j].bt[k][i] = bt[k][i][j];
			}
		}
	}
    //qDebug() << "Turn:"  << rowInformation.scoreInfo[0].turn ;
	
}

void Channel::clearRowinfo()
{
    initScore();
    playerNO = -1;
    breakFlag = false;
    comboBox->setEnabled(false);
    pushButton->setEnabled(false);
    for (int i = 0; i < 3; i++)
    {
        labelListA[i]->clear();
        labelListB[i]->clear();
    }
    tcpCtrl.close();
}

void Channel::getPushButtonDown()
{
    QObject *tmpPusbButton=QObject::sender ();
    if(tmpPusbButton->objectName()=="channelPushButton")
    {
        channelWidget->show();
        foodWidget->hide();
        historyWidget->hide();
    }
    else if(tmpPusbButton->objectName()=="historyPushButton")
    {
        channelWidget->hide();
        foodWidget->hide();
        historyWidget->show();
    }
    else if(tmpPusbButton->objectName()=="foodPushButton")
    {
        channelWidget->hide();
        foodWidget->show();
        historyWidget->hide();
    }

}

void Channel::callService()
{
	tcpCtrl.connectToServer(number, dataTransform::CALL_SERVICE);
	QMessageBox msgBox(channelNumWidget);
	msgBox.setWindowTitle("提示");
	msgBox.setText(tr("已经呼叫服务员，请稍后"));
	msgBox.exec();
}

void Channel::unableCombobox()
{
	initScore();
	turn = 0;
	currentPlayer = 0;
	if (comboBox->currentIndex() > restCount - 1)
	{
		comboBox->setCurrentIndex(restCount - 1);
	}
	playerNO = comboBox->currentIndex();
	comboBox->setEnabled(false);
	pushButton->setEnabled(false);
    for (int i = 0; i < 3; i++)
    {
        labelListA[i]->clear();
        labelListB[i]->clear();
    }
	showScore();
}

void Channel::getChannelShow(int num)
{
    num++;
    for(int i=0;i<num;i++)
    {
        widgetList[i]->show();
    }
    for(int i=num;i<3;i++)
    {
        widgetList[i]->hide();
    }
}

void Channel::getHistoryShow(int r, int c)
{
	if (c == 3)
	{
		QMessageBox msgBox(historyTableWidget);
		msgBox.setWindowTitle("详细得分");
		msgBox.setText(historyStat[r] + "\n" + historyDetail[r]);
		msgBox.exec();
	}
}

void Channel::writeHistory(QString name, int currentP, int historyScore)
{
	int tempRow = historyTableWidget->rowCount();
	historyTableWidget->insertRow(tempRow);
	for (int i = 0; i < 4; i++)
	{
		QTableWidgetItem *abc = new QTableWidgetItem;
		abc->setFlags(Qt::ItemIsSelectable | Qt::ItemIsTristate | Qt::ItemIsEnabled);
		abc->setTextAlignment(Qt::AlignCenter);
		historyTableWidget->setItem(tempRow, i, abc);

	}
	historyTableWidget->item(tempRow, 0)->setText(name);
	QTime timeNow = QTime::currentTime();
	historyTableWidget->item(tempRow, 1)->setText(timeNow.toString("h:m"));
	QString tempS;
	historyTableWidget->item(tempRow, 2)->setText(tempS.setNum(historyScore));
	historyStat.push_back(labelListA[currentP]->text());
	historyDetail.push_back(labelListB[currentP]->text());
}

void Channel::orderService()
{
	QMessageBox msgBox(foodTableWidget);
	msgBox.setText(tr("是否确认？"));
	msgBox.setWindowTitle("友情提示");
	acc = msgBox.addButton("确认", QMessageBox::AcceptRole);
	cncel = msgBox.addButton("取消", QMessageBox::RejectRole);
	connect(acc, SIGNAL(clicked()), this, SLOT(orderNetwork()));
	msgBox.exec();
}

void Channel::orderNetwork()
{
	int i, count = 0;
	RowInfo goodsInfo;
	for (i = 0; i < maxCount; i++)
	{
		if (foodTableWidget->item(i, 4) != 0)
		{		
			goodsInfo.buyGoodsInfo.goodsId.append(foodTableWidget->item(i, 0)->text().toInt());
			goodsInfo.buyGoodsInfo.goodsCount.append(foodTableWidget->item(i, 4)->text().toInt());
			count++;
		}
	}
	goodsInfo.buyGoodsInfo.goodsTypeSize = count;
	tcpCtrl.connectToServer(number, dataTransform::CALL_GOODS, goodsInfo);

	QMessageBox msgBox(foodTableWidget);
	msgBox.setWindowTitle("提示");
	msgBox.setText(tr("餐饮已点，请稍候"));
	msgBox.exec();
}

void Channel::initScore()
{
	int i, j, k;
    breakFlag = true;
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 3; j++)
		{
			score[i][j] = 0;
			str[i][j] = "\0";
		}
	}
	for(i = 0; i < 4 ; i++)
		for(j = 0; j < 10; j++)
			for(k = 0; k < 3; k++)
				bt[i][j][k] = 11;
}

void Channel::showStat(const int n, const int p)
{
	int i, j, count_blank;
	QString s;
	for(i = 0; i <= n; i++)
	{
		count_blank = 6 - str[i][p].length();
		s.append(str[i][p]);
		for (j = 0; j < count_blank; j++)
		{
			s.append(" ");
		}
	}
	labelListA[p]->setText(s);
	getRowInfo(n, p);
	tcpCtrl.connectToServer(number, dataTransform::ROW_SCORE, rowInformation);
}

int Channel::getNum()
{
	bool ok;
	int tempNum;
    tempNum = QInputDialog::getInteger(this, tr("击倒球数"), tr("输入："), NULL, 0, 10, 1, &ok);
    if (ok)
    {
        return tempNum;
    }
    return 10;
}

void Channel::getScore(const int n, const int p)
{
	int i, j, count_blank;
	QString s;
	QString tmp;
	if(0 == n)
	{
		if(-2 == bt[3][n][p])
			score[n][p] = bt[0][n][p] + bt[2][n][p];
		else if(-1 == bt[3][n][p])
			score[n][p] = bt[0][n][p] + bt[1][n][p] + bt[2][n][p];
		else
			score[n][p] = bt[0][n][p] + bt[1][n][p];
	}
	else if(n > 0 && n < 10)
	{
		if(-2 == bt[3][n][p])
			score[n][p] = bt[0][n][p] + bt[2][n][p] + score[n-1][p];
		else if(-1 == bt[3][n][p])
			score[n][p] = bt[0][n][p] + bt[1][n][p] + bt[2][n][p] + score[n-1][p];
		else
			score[n][p] = bt[0][n][p] + bt[1][n][p] + score[n-1][p];
	}
	else
		perror("出错");
	for(i = 0; i <= n; i++)
	{
		tmp.setNum(score[i][p]);
		count_blank = 6 - tmp.length();
		s.append(tmp);
		for (j = 0; j < count_blank; j++)
		{
			s.append(" ");
		}
	}
	labelListB[p]->setText(s);
	getRowInfo(n, p);
	tcpCtrl.connectToServer(number, dataTransform::ROW_SCORE, rowInformation);
}

void Channel::showScore()
{
	int tmp1, tmp2;
	QString s;
// 	playerNO = comboBox->currentIndex();
// 	turn = 0;
    while (turn < 10 && breakFlag)
	{
        while (currentPlayer <= playerNO && breakFlag)
		{
            if(!breakFlag)
                break;
			tmp1 = getNum();
			if (10 == tmp1)
			{			
				bt[0][turn][currentPlayer] = 10;
				bt[3][turn][currentPlayer] = -2;
				str[turn][currentPlayer] = "X";
				showStat(turn, currentPlayer);
				if(1 == turn)
				{
					if(-1 == bt[3][0][currentPlayer])
					{
						bt[2][0][currentPlayer] = 10;
						getScore(0, currentPlayer);
					}
				}
				if(turn > 1 && turn < 10)
				{
					if(-1 == bt[3][turn-1][currentPlayer])
					{
						bt[2][turn-1][currentPlayer] = 10;
						getScore(turn-1, currentPlayer);
					}
					else if(-2 == bt[3][turn-1][currentPlayer] && -2 == bt[3][turn-2][currentPlayer])
					{
						bt[2][turn-2][currentPlayer] = 20;
						getScore(turn-2, currentPlayer);
					}
				}
				if(9 == turn)
				{
                    if(!breakFlag)
                        break;
					bt[1][9][currentPlayer] = getNum();
					if(10 == bt[1][9][currentPlayer])
						str[9][currentPlayer] += 'X';
					else
						str[9][currentPlayer] += s.setNum(bt[1][9][currentPlayer]);
					showStat(9, currentPlayer);
					if(-2 == bt[3][8][currentPlayer])
					{
						bt[2][8][currentPlayer] = 10 + bt[1][9][currentPlayer];
						getScore(8, currentPlayer);
					}
                    if(!breakFlag)
                        break;
					tmp2 = getNum(); 
					if(10 == tmp2)
						str[9][currentPlayer] += 'X';
					else if(bt[1][9][currentPlayer] < 10 && bt[1][9][currentPlayer] + tmp2 == 10)
						str[9][currentPlayer] += '/';
					else if(0 == tmp2)
						str[9][currentPlayer] += '-';
					else
						str[9][currentPlayer] += s.setNum(tmp2);
					bt[2][9][currentPlayer] = bt[1][9][currentPlayer] + tmp2;
					showStat(9, currentPlayer);
					getScore(9, currentPlayer);
				}
			}
			else if(tmp1 < 10)
			{
				bt[0][turn][currentPlayer] = tmp1;
				str[turn][currentPlayer].setNum(tmp1);
				showStat(turn, currentPlayer);
				if(1 == turn)
				{
					if(-1 == bt[3][0][currentPlayer])
					{
						bt[2][0][currentPlayer] = tmp1;
						getScore(0, currentPlayer);
					}
				}
				if(turn > 1 && turn < 10)
				{
					if(-1 == bt[3][turn-1][currentPlayer])
					{
						bt[2][turn-1][currentPlayer] = tmp1;
						getScore(turn-1, currentPlayer);
					}
					else if(-2 == bt[3][turn-1][currentPlayer] && -2 == bt[3][turn-2][currentPlayer])
					{
						bt[2][turn-2][currentPlayer] = 10 + tmp1;
						getScore(turn-2, currentPlayer);
					}
				}
                if(!breakFlag)
                    break;
				bt[1][turn][currentPlayer] = getNum();
				if(turn > 0 && turn < 10)
				{
					if(-2 == bt[3][turn-1][currentPlayer])
					{
						bt[2][turn-1][currentPlayer] = bt[0][turn][currentPlayer] + bt[1][turn][currentPlayer];
						getScore(turn-1, currentPlayer);
					}
				}
				if(bt[0][turn][currentPlayer] + bt[1][turn][currentPlayer] == 10)
				{
					bt[3][turn][currentPlayer] = -1;
					str[turn][currentPlayer] += '/';
					showStat(turn, currentPlayer);
					if(9 == turn)
					{
						if(-2 == bt[3][8][currentPlayer])
						{
							bt[2][8][currentPlayer] = 10;
							getScore(8, currentPlayer);
						}
                        if(!breakFlag)
                            break;
						tmp2 = getNum(); 
						if(10 == tmp2)
							str[9][currentPlayer] += 'X';
						else if(0 == tmp2)
							str[9][currentPlayer] += '-';
						else
							str[9][currentPlayer] += s.setNum(tmp2);
						bt[2][9][currentPlayer] = tmp2;
						showStat(9, currentPlayer);
						getScore(9, currentPlayer);
					}
				}
				if(bt[1][turn][currentPlayer] == 0)
				{
					str[turn][currentPlayer] += '-';
					showStat(turn, currentPlayer);
					getScore(turn, currentPlayer);
				}
				if(bt[1][turn][currentPlayer] != 0 && bt[0][turn][currentPlayer] + bt[1][turn][currentPlayer] < 10)
				{
					str[turn][currentPlayer] += s.setNum(bt[1][turn][currentPlayer]);
					showStat(turn, currentPlayer);
					getScore(turn, currentPlayer);
				}
			}
			currentPlayer++;
		}
		turn++;
		currentPlayer = 0;
	}
	
	for (int i = 0; i <= playerNO; i++)
	{
		writeHistory(QString('A' + i).toLocal8Bit(), i, score[9][i]);
	}
	tcpCtrl.connectToServer(number, dataTransform::END_ONE);
    //qDebug() << "Client end one";
	//tcpCtrl.connectToServer(number, dataTransform::CALL_BEGIN);
}

void Channel::setPortAndID(int port, int id)
{
    number=id;
    server = new CustomerTcpServer;

    if (!server->listen(QHostAddress::Any, port))
    {
        QMessageBox::critical(NULL, "错误", "\n\n\n监听端口错误\n\n\n");
        return;
    }



    this->resize(800, 600);
        //layOutWidget = new QWidget(this);
        stackWidget = new QStackedWidget(this);
//	stackWidget->setGeometry(0, 60, 610, 340);
    foodWidget = new QWidget(stackWidget);
    foodWidget->setGeometry(QRect(0, 0, 600, 330));
        verticalLayout3 = new QVBoxLayout();
    foodTableWidget = new QTableWidget(foodWidget);
    foodTableWidget->setGeometry(QRect(10, 0, 580, 290));
        verticalLayout3->addWidget(foodTableWidget);
        if(foodTableWidget->columnCount() < 5)
                foodTableWidget->setColumnCount(5);
        //foodTableWidget->setRowCount(10);

        QTableWidgetItem *__qtablewidgetitem0 = new QTableWidgetItem();
        __qtablewidgetitem0->setText("商品编号");
        foodTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem0);

        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setText("餐饮名称");
        foodTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);

        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setText("单价");
        foodTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setText("备注描述");
        foodTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem_4 = new QTableWidgetItem();
        __qtablewidgetitem_4->setText("购买数量");
        foodTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem_4);
        foodTableWidget->setSortingEnabled(true);
        QString s[10];
/*
        for(int i = 0; i < 10; i++)
        {
                for(int j = 0; j < 3; j++)
                {
                        QTableWidgetItem *ab = new QTableWidgetItem;
                        ab->setFlags(Qt::ItemIsSelectable | Qt::ItemIsTristate | Qt::ItemIsEnabled);
                        foodTableWidget->setItem(i, j, ab);
                        foodTableWidget->item(i, j)->setText(s[i].setNum(i));
                }
        }
*/

        QSqlQuery sql;

        sql.prepare("SELECT count(*) FROM goods;");
        sql.exec();
        sql.next();
        maxCount = sql.value(0).toInt();
        foodTableWidget->setRowCount(maxCount);
        sql.prepare("select goods_id, goods_name,goods_sale_price, goods_remark from goods;");
        sql.exec();
        int goodsRowNo=0;
        while (sql.next())
        {
                for (int j=0; j<4; j++)
                {
                                foodTableWidget->setItem(goodsRowNo, j, new QTableWidgetItem(sql.value(j).toString()));
                                foodTableWidget->item(goodsRowNo, j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsTristate | Qt::ItemIsEnabled);
                                foodTableWidget->item(goodsRowNo, j)->setTextAlignment(Qt::AlignCenter);
                }
                foodTableWidget->setItem(goodsRowNo,4,new QTableWidgetItem(sql.value(4).toString()));
                foodTableWidget->item(goodsRowNo, 4)->setTextAlignment(Qt::AlignCenter);
                goodsRowNo++;
        }

        okPushButton = new QPushButton(tr("选定"), foodWidget);
        //QRect *okPos = new QRect;
        //okPos->moveBottomRight();
        okPushButton->setGeometry(260, 295, 80, 35);
        //okPushButton->setGeometry(okPos);
        okPushButton->setObjectName("okPushButton");
        verticalLayout3->addWidget(okPushButton);
        verticalLayout3->addWidget(foodTableWidget);

    historyWidget = new QWidget(stackWidget);
    historyWidget->setGeometry(QRect(0, 0, 600, 330));
        historyWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        verticalLayout4 = new QVBoxLayout(historyWidget);

    historyTableWidget = new QTableWidget(historyWidget);
        historyTableWidget->setGeometry(QRect(10, 0, 580, 330));
        historyTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        verticalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
//	verticalLayout4->addItem(verticalSpacer_8);
        verticalLayout4->addWidget(historyTableWidget);
        verticalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
//	verticalLayout4->addItem(verticalSpacer_9);

        gridLayout1 = new QGridLayout(historyWidget);
        gridLayout1->addWidget(historyTableWidget, 0, 0, 1, 1);

        gridLayout2 = new QGridLayout(stackWidget);
        gridLayout2->addLayout(verticalLayout4, 0, 0, 1, 1);
        stackWidget->setLayout(gridLayout2);

        if(historyTableWidget->columnCount() < 4)
                historyTableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setText("选手名称");
        historyTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setText("比赛时间");
        historyTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setText("得分");
        historyTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setText("点击查看");
        historyTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        historyTableWidget->setSortingEnabled(true);

    channelWidget = new QWidget(stackWidget);
        channelWidget->setGeometry(QRect(0, 60, 600, 330));
        verticalLayout = new QVBoxLayout(channelWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
    channelNumWidget = new QWidget(channelWidget);
//    channelNumWidget->setGeometry(QRect(70, 50, 451, 261));

    widget = new QWidget(channelWidget);
//    widget->setGeometry(QRect(10, 10, 581, 22));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);
        verticalLayout->addItem(verticalSpacer_5);
        verticalLayout->addWidget(widget);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);
        verticalLayout->addItem(verticalSpacer);
        verticalLayout->addWidget(channelNumWidget);
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        verticalLayout->addItem(verticalSpacer_6);
    horizontalLayout_2 = new QHBoxLayout(widget);
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_7);



        QString ss, str;
        ss.setNum(number);
        str.append("第");
        str.append(ss);
        str.append("球道");
        labelNO = new QLabel(widget);
        labelNO->setText(str);
        horizontalLayout_2->addWidget(labelNO);
    label = new QLabel(tr("球道人数："), widget);
    horizontalLayout_2->addWidget(label);
    horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    horizontalLayout_2->addItem(horizontalSpacer_6);

    comboBox = new QComboBox(widget);
    comboBox->addItems(QStringList()<<"1"<<"2"<<"3");
    comboBox->setEnabled(true);
    comboBox->setEditable(false);
    horizontalLayout_2->addWidget(comboBox);
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout_2->addItem(horizontalSpacer_9);

        pushButton = new QPushButton(widget);
        pushButton->setText(tr("确认人数"));
        horizontalLayout_2->addWidget(pushButton);

    horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_8);

//	verticalLayout->addLayout(horizontalLayout_2);


    widget1 = new QWidget(this);
//    widget1->setGeometry(QRect(0, 0, 600, 50));

        horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);
    horizontalSpacer_4 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer_4);
    channelPushButton = new QPushButton(tr("球道信息"),widget1);
    channelPushButton->setObjectName("channelPushButton");
    horizontalLayout->addWidget(channelPushButton);
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer);
    historyPushButton = new QPushButton(tr("历史信息"),widget1);
    historyPushButton->setObjectName("historyPushButton");
    horizontalLayout->addWidget(historyPushButton);
    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer_2);
    foodPushButton = new QPushButton(tr("食品饮料"),widget1);
    foodPushButton->setObjectName("foodPushButton");
    horizontalLayout->addWidget(foodPushButton);
    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer_3);
    callPushButton = new QPushButton(tr("呼叫服务员"),widget1);
    callPushButton->setObjectName("callPushButton");
    horizontalLayout->addWidget(callPushButton);
    horizontalSpacer_5 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer_5);

        stackWidget->addWidget(channelWidget);
        stackWidget->addWidget(historyWidget);
        stackWidget->addWidget(foodWidget);

        verticalLayout2 = new QVBoxLayout();
        verticalLayout2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Fixed, QSizePolicy::Fixed);
        verticalLayout2->addItem(verticalSpacer_3);
        verticalLayout2->addLayout(horizontalLayout);
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Fixed, QSizePolicy::Fixed);
        verticalLayout2->addItem(verticalSpacer_4);
        verticalLayout2->addWidget(stackWidget);
        verticalSpacer_7 = new QSpacerItem(20, 60, QSizePolicy::Fixed, QSizePolicy::Fixed);
        verticalLayout2->addItem(verticalSpacer_7);
        gridLayout = new QVBoxLayout(this);
        gridLayout->addLayout(verticalLayout2);
        setLayout(gridLayout);
    foodWidget->hide();
    historyWidget->hide();
        comboBox->setEnabled(false);
        pushButton->setEnabled(false);

    initChannelLayout();
    initConnection();
        getChannelShow(0);
        initScore();

        //tcpCtrl.connectToServer(number, dataTransform::CALL_BEGIN, rowInformation);
    //tcpCtrl.connectToServer(number, dataTransform::CALL_BEGIN);
        QObject::connect(&tcpCtrl, SIGNAL(dataReceived(int)), this, SLOT(initRestCount(int)));
    //QObject::connect(&tcpCtrl, SIGNAL(dataReceived(RowInfo)), this, SLOT(intRowinfo(RowInfo)));
    QObject::connect(server, SIGNAL(beginPlay(int)), this, SLOT(initRestCount(int)));
    QObject::connect(server, SIGNAL(changeRow(RowInfo)), this, SLOT(intRowinfo(RowInfo)));
    QObject::connect(server, SIGNAL(addMoney(int)), this, SLOT(addRestCount(int)));
    QObject::connect(server, SIGNAL(dissMiss()), this, SLOT(clearRowinfo()));
    //QObject::connect(server, SIGNAL(newConnection()), this, SLOT(initRestCount(int)));
//	showScore();
}

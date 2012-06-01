#include "rowInfo.h"
#include <QFile>
#include <QDataStream>
#include <QObject>
#include <QMessageBox>

bool RowInfo::writeInfo(int rowId)
{
	QString fileName;
	fileName.setNum(rowId);
	QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
	{
        //QMessageBox::warning(NULL, "ERROR", "Cannot write file " + fileName + " ERROR:" + file.errorString());
			//.arg(file.fileName())
			//.arg(file.errorString()));
		return false;
	}
	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_4_1);
	totalPlayerCount = (totalPlayerCount<scoreInfo.size() ? totalPlayerCount : scoreInfo.size());
	currentPlayerNo = (currentPlayerNo < totalPlayerCount ? currentPlayerNo : 0);
	out << quint16(restCount) 
		<< (restTime=="" ? "-" : restTime)
		<< (state=="" ? "-" : state)
		<< (type=="" ? "-" : type)
		<< quint16(useType)
		<< quint16(totalPlayerCount)
		<< quint16(currentPlayerNo);


	for (int i=0; i<totalPlayerCount; i++)
	{
		out << quint16(scoreInfo[i].theEndFlag)
			<< quint16(scoreInfo[i].turn);
		
		for (int j=0; j<dataTransform::SCORE_SIZE; j++)
		{
			out << quint16(scoreInfo[i].score[j])
				<< (scoreInfo[i].str[j]=="" ? "-" : scoreInfo[i].str[j]);
		}

        for (int j=0; j<dataTransform::BT_ROW_SIZE ; j++)
        {
            for (int k=0; k<dataTransform::SCORE_SIZE; k++)
            {
                out << qint16(scoreInfo[i].bt[j][k]);
            }
        }
	}
	
	buyGoodsInfo.goodsTypeSize = (buyGoodsInfo.goodsTypeSize < buyGoodsInfo.goodsId.size() 
		? buyGoodsInfo.goodsTypeSize : buyGoodsInfo.goodsId.size());
	buyGoodsInfo.goodsTypeSize = (buyGoodsInfo.goodsTypeSize < buyGoodsInfo.goodsCount.size()
		? buyGoodsInfo.goodsTypeSize : buyGoodsInfo.goodsCount.size());
	out << quint16(buyGoodsInfo.goodsTypeSize);
	for (int i=0; i<buyGoodsInfo.goodsTypeSize; i++)
	{
		out << quint16(buyGoodsInfo.goodsId[i]);
		out << quint16(buyGoodsInfo.goodsCount[i]);
	}

	return true;
}

//bool RowInfo::writeInfo(QString rowId)
//{
//	
//}

bool RowInfo::readInfo(int rowId)
{
	QString fileName;
	fileName.setNum(rowId);
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) 
	{
        //QMessageBox::warning(NULL, "ERROR", "Cannot read file " + fileName + " ERROR:" + file.errorString());
		return false;
	}
	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_4_1);
	
	quint16 restCount16, useType16, totalPlayerCount16, currentPlayerNo16;
	
	in >> restCount16
		>> restTime
		>> state
		>> type
		>> useType16
		>> totalPlayerCount16
		>> currentPlayerNo16;

	restCount = restCount16;
	useType = useType16;
	totalPlayerCount = totalPlayerCount16;
	currentPlayerNo = currentPlayerNo16;
	quint16 theEndFlag16, turn16, score16;
    qint16 bt16;
	scoreInfo.resize(totalPlayerCount16);
	for (int i=0; i<totalPlayerCount; i++)
	{
		in >> theEndFlag16
			>> turn16;

		scoreInfo[i].theEndFlag = theEndFlag16;
		scoreInfo[i].turn = turn16;

		for (int j=0; j<dataTransform::SCORE_SIZE; j++)
		{
			in >> score16
				>> scoreInfo[i].str[j];
			scoreInfo[i].score[j] = score16;
			if (scoreInfo[i].str[j]=="-")
				scoreInfo[i].str[j].clear();
        }

        for (int j=0; j<dataTransform::BT_ROW_SIZE ; j++)
        {
            for (int k=0; k<dataTransform::SCORE_SIZE; k++)
            {
                in >> bt16;
                scoreInfo[i].bt[j][k] = bt16;
            }
        }
	}

	quint16 goodsTypeSize16, goodsId16, goodsCount16;
	in >> goodsTypeSize16;
	buyGoodsInfo.goodsTypeSize = goodsTypeSize16;
	buyGoodsInfo.goodsId.resize(goodsTypeSize16);
	buyGoodsInfo.goodsCount.resize(goodsTypeSize16);
	for (int i=0; i<buyGoodsInfo.goodsTypeSize; i++)
	{
		in >> goodsId16;
		buyGoodsInfo.goodsId[i] = goodsId16;
		in >> goodsCount16;
		buyGoodsInfo.goodsCount[i] = goodsCount16;
	}

	return true;
}

//bool RowInfo::readInfo(QString rowId)
//{
//	
//	return true;
//}

void RowInfo::clearScore()
{
	for (int i=0; i < dataTransform::SCORE_SIZE; i++)
	{

	}
}

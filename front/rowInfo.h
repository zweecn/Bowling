#ifndef _ROW_INFO_H
#define _ROW_INFO_H
#include <QVector>
#include <QString>
#include <QTime>
#include "dataInfo.h"

class RowInfo
{
public:
	RowInfo(){};
	~RowInfo(){};
	//int id;
	enum{USE_TIME, USE_COUNT};
	QString state;
	QString type;
	int useType;
	int restCount;
	QString vipId;
	QString timeBegin;
    QString restTime;

	dataTransform::GoodsInfo buyGoodsInfo;
	int totalPlayerCount;
	int currentPlayerNo;
	QVector<dataTransform::ScoreInfo> scoreInfo;//[dataTransform::SCORE_SIZE];
	
	bool writeInfo(int rowId);
	//bool writeInfo(QString rowId);
	bool readInfo(int rowId);
	//bool readInfo(QString rowId);
	
	void clearScore();

	/*QVector<int> buyGoodsId;
	QVector<int> buyGoodsCount;
	QVector<int> score;*/

};

#endif

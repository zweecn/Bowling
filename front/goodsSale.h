#ifndef _GOODS_SALE_H
#define _GOODS_SALE_H
#include "ui_goodsSale.h"
#include <QDialog>
#include "rowInfo.h"
#include <QMap>
#include <QList>
#include <QSqlQuery>

//#define COLUMN_SIZE 5
//#define MAX_ROW_SIZE 64


class goodsSaleItem
{
public:
    int id;
    int count;
    double price;

    QString idString;
    QString countString;
    QString priceString;
};

class GoodsSale : public QDialog
{
	Q_OBJECT
public:
	GoodsSale(QDialog *parent = 0);
	~GoodsSale();

	void setBuyInfo(const int rowID, const QMap<int, RowInfo>& info);
	void prepareShow();
	private slots:
		void saleOk();
private:
    enum
    {
        COLUMN_SIZE=5,
        MAX_ROW_SIZE=64,
    };
	Ui::goodsSaleUI ui;
	int buyerRowId;
    //QVector<QTableWidgetItem> item;
	QVector<QString> itemText;
	QMap<int, RowInfo> rowInfo;

    QList<goodsSaleItem> saleItem;
    //QSqlQuery sqlInstF, sqlInstG, sqlUpdateG;
};

#endif


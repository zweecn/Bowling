#include "goodsSale.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDate>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

GoodsSale::GoodsSale(QDialog *parent /* = 0 */) : QDialog(parent)
{
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	ui.setupUi(this);

    itemText.resize(MAX_ROW_SIZE*COLUMN_SIZE);
    //item.resize(itemText.size());
    ui.tableWidget->setColumnCount(COLUMN_SIZE);
    ui.tableWidget->setRowCount(MAX_ROW_SIZE);
    for (int i=0; i<MAX_ROW_SIZE; i++)
    {
        for (int j=0; j<COLUMN_SIZE; j++)
        {
            ui.tableWidget->setItem(i,j,new QTableWidgetItem);
            ui.tableWidget->item(i,j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsTristate | Qt::ItemIsSelectable);
            ui.tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    QObject::connect(ui.okButton, SIGNAL(clicked()), this, SLOT(saleOk()));
}
GoodsSale::~GoodsSale()
{

}

void GoodsSale::prepareShow()
{

	//int rowSize = rowInfo[buyerRowId].buyGoodsId.size();
	int rowSize = rowInfo[buyerRowId].buyGoodsInfo.goodsTypeSize;

	QString buyGoodsId, buyGoodsCount;
	

	/*QString test;
	test.setNum(rowSize);
	QMessageBox::critical(0, "之后", "购买个数"+test);	 */

	int rowNo=0;
    for (int i=0; i<rowSize && i<MAX_ROW_SIZE; i++)
	{
		/*buyGoodsId.setNum(rowInfo[buyerRowId].buyGoodsId[i]);
		buyGoodsCount.setNum(rowInfo[buyerRowId].buyGoodsCount[i]);*/
		buyGoodsId.setNum(rowInfo[buyerRowId].buyGoodsInfo.goodsId[i]);
		buyGoodsCount.setNum(rowInfo[buyerRowId].buyGoodsInfo.goodsCount[i]);

		QSqlQuery query("SELECT goods_name, goods_sale_price FROM goods WHERE goods_id="+buyGoodsId);
		query.exec();
		if (!query.next())
		{
			QMessageBox::critical(NULL, "错误", "没有商品号为 " + buyGoodsId + " 的商品");
		}
		else
		{
            goodsSaleItem item;
            item.id = rowInfo[buyerRowId].buyGoodsInfo.goodsId[i];
            item.idString = buyGoodsId;
            item.count = rowInfo[buyerRowId].buyGoodsInfo.goodsCount[i];
            item.countString = buyGoodsCount;
            item.price = query.value(1).toDouble();//itemText[rowNo*COLUMN_SIZE+2].toDouble();
            item.priceString.setNum(item.price);
            itemText[rowNo*COLUMN_SIZE+2] = item.priceString;
            saleItem.push_back(item);

			itemText[rowNo*COLUMN_SIZE] = buyGoodsId;
			itemText[rowNo*COLUMN_SIZE+1] = query.value(0).toString();
            //itemText[rowNo*COLUMN_SIZE+2].setNum(query.value(1).toDouble());
			itemText[rowNo*COLUMN_SIZE+3] = buyGoodsCount;
			//itemText[rowNo*COLUMN_SIZE+4].setNum(query.value(1).toInt() * rowInfo[buyerRowId].buyGoodsCount[i]);
			itemText[rowNo*COLUMN_SIZE+4].setNum(query.value(1).toInt() * rowInfo[buyerRowId].buyGoodsInfo.goodsCount[i]);
			rowNo++;
        }
	}
	int totalPrice=0;
	QString totalPriceString;
	for (int i=0; i<rowSize; i++)
	{
		for (int j=0; j<COLUMN_SIZE; j++)
		{
            //item[i*COLUMN_SIZE+j].setText(itemText[i*COLUMN_SIZE+j]);
            //item[i*COLUMN_SIZE+j].setTextAlignment(Qt::AlignCenter);
            //ui.tableWidget->setItem(i,j,&item[i*COLUMN_SIZE+j]);
            ui.tableWidget->item(i,j)->setText(itemText[i*COLUMN_SIZE+j]);
		}
		totalPrice += itemText[i*COLUMN_SIZE+COLUMN_SIZE-1].toInt();
	}
	totalPriceString.setNum(totalPrice);
	QString rowIdString;
	rowIdString.setNum(buyerRowId);
	ui.totalLabel->setText("球道号: " + rowIdString + "  合计: " + totalPriceString);
}

void GoodsSale::setBuyInfo(const int rowID, const QMap<int, RowInfo>& info)
{
	buyerRowId = rowID;
	rowInfo = info;
}

void GoodsSale::saleOk()
{
    //int size = (buyId.count() < buyCount.count() ? buyId.count() : buyCount.count());
    //QString id;
    //int size = rowInfo[buyerRowId].buyGoodsInfo.goodsTypeSize;
    //QString minusSize;
    int size = saleItem.size();
    for (int i=0; i<size; i++)
    {
       // qDebug() << "购买id:" << saleItem[i].idString << " 购买cnt:"
       //         << saleItem[i].countString << "单价:" << saleItem[i].price << saleItem[i].priceString;
        //id.setNum(rowInfo[buyerRowId].buyGoodsInfo.goodsId[i]);
        //minusSize.setNum(rowInfo[buyerRowId].buyGoodsInfo.goodsCount[i]);
        QSqlQuery sqlUpdateG;
        sqlUpdateG.prepare("update goods set goods_count=goods_count-"
                        + saleItem[i].countString
                        + " where goods_id="
                        + saleItem[i].idString + " and goods_count>=" + saleItem[i].countString);
        if (!sqlUpdateG.exec())
        {
            QMessageBox::critical(NULL, "数据库更新错误", "错误信息\n" + sqlUpdateG.lastError().text());
        }

        QSqlQuery sql;
        sql.prepare("INSERT INTO goods_record VALUES (NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
            sql.addBindValue(saleItem[i].id);
            sql.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
            sql.addBindValue(saleItem[i].price); //price
            sql.addBindValue(saleItem[i].count); //count
            //sql.addBindValue(gr_employee_id);
            //sql.addBindValue(gr_agent_id);
            //sql.addBindValue(gr_item_id);
            sql.addBindValue(1);
            sql.addBindValue(1);
            sql.addBindValue(1);

            sql.addBindValue("售出");
            sql.addBindValue("商品");
         if (!sql.exec())
         {
            QMessageBox::critical(NULL, "数据库更新错误", "错误信息\n" + sql.lastError().text());
         }

         QSqlQuery sqlInst;
         sqlInst.prepare("insert into finance values(NULL, ?,?,?, ?, ?)");
         sqlInst.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
         sqlInst.addBindValue("收入");
         sqlInst.addBindValue("商品销售");
         double saleP = saleItem[i].price * saleItem[i].count;
         sqlInst.addBindValue(saleP);
         //sqlInst.addBindValue(f_employee_id);
         sqlInst.addBindValue(1);
         if (!sqlInst.exec())
         {
              QMessageBox::critical(NULL, "数据库更新错误", "错误信息\n" + sqlInst.lastError().text());
         }
    }
	this->hide();
}

#include "teachInfo.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDate>
#include <QSqlRecord>

TeachInfo::TeachInfo(QDialog *parent /* = 0 */) : QDialog(parent)
{
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	ui.setupUi(this);
	
	QObject::connect(ui.okButton, SIGNAL(clicked()), this, SLOT(close()));
}

TeachInfo::~TeachInfo()
{
	item.clear();
	itemText.clear();
}

void TeachInfo::showTeachInfo()
{
	query.prepare("SELECT COUNT(*) FROM teach_info t");
	query.exec();
	query.next();
	int maxSize;
	if ((maxSize = query.value(0).toInt())>0)
	{
		item.resize(maxSize*selectProportyNum);
		itemText.resize(maxSize*selectProportyNum);
	}

	query.prepare("SELECT coach_name, teach_date_start, teach_date_end, timediff(teach_date_end, teach_date_start), teach_stu_num, teach_row_id \
		FROM teach_info t, coach c WHERE t.coach_id = c.coach_id order by teach_date_start");
	query.exec();
	int beginIndex = query.record().indexOf("teach_date_start");
	int endIndex = query.record().indexOf("teach_date_end");
	int nameIndex = query.record().indexOf("coach_name");
	int timeStamp = query.record().indexOf("timediff(teach_date_end, teach_date_start)");
	int stuNumIndex = query.record().indexOf("teach_stu_num");
	int rowIdIndex = query.record().indexOf("teach_row_id");
	int resultNum=0;

	while(query.next())
	{	
		itemText[resultNum*selectProportyNum+0] = query.value(beginIndex).toDateTime().toString("yyyy-MM-dd hh:mm");		//Start time
		itemText[resultNum*selectProportyNum+1] = query.value(endIndex).toDateTime().toString("yyyy-MM-dd hh:mm");
		itemText[resultNum*selectProportyNum+2] = query.value(nameIndex).toString();	
		itemText[resultNum*selectProportyNum+3] = query.value(timeStamp).toTime().toString("hh:mm");
		itemText[resultNum*selectProportyNum+4] = query.value(stuNumIndex).toString();						//Student number
		itemText[resultNum*selectProportyNum+5] = query.value(rowIdIndex).toString();						//Teach row
		resultNum++;
	}
	ui.tableWidgetTeachInfo->setColumnCount(selectProportyNum);
	ui.tableWidgetTeachInfo->setRowCount(resultNum);
	for (int i=0; i<resultNum; i++)
	{
		for (int j=0; j<selectProportyNum; j++)
		{
			item[i*selectProportyNum+j].setText(itemText[i*selectProportyNum+j]);
			ui.tableWidgetTeachInfo->setItem(i,j,&item[i*selectProportyNum+j]);
		}
	}
}

void TeachInfo::setCoach(const QString& name)
{
	coachName = name;
}

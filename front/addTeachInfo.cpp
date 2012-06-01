#include "addTeachInfo.h"
#include <QMessageBox>
#include <QSqlError>

AddTeachInfo::AddTeachInfo(QDialog *parent /* = 0 */) : QDialog(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.okButton, SIGNAL(clicked()), this, SLOT(add()));
	
	QObject::connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}
AddTeachInfo::~AddTeachInfo()
{

}

void AddTeachInfo::add()
{
	QDateTime teachStart(ui.dateTimeEditTeachBegin->dateTime());
	QDateTime teachEnd(ui.dateTimeEditTeachEnd->dateTime());
	if (teachEnd<=teachStart)
	{
		QMessageBox::critical(0, "错误", "结束时间应该在开始时间之前");
		return;
	}

	rowId = ui.comboBoxTeachRow->currentText();
	teachStuNum = ui.lineEditPeopleCount->text();
	/*
	//QDateTime timeTemp;
	//timeTemp.setTime_t(teachEnd.toTime_t()-teachBegin.toTime_t());
	//timeStamp = timeTemp.toString("hh:mm");
	
	QStringList temp1, temp2, beginTemp, endTemp;
	temp1 = teachBegin.toString("yy-MM-dd hh:mm").split(" ");
	temp2 = teachEnd.toString("yy-MM-dd hh:mm").split(" ");
	beginTemp = temp1[1].split(":");
	endTemp = temp2[1].split(":");
	QString timeTemp1, timeTemp2;
	int h, m;
	h = endTemp[0].toInt()-beginTemp[0].toInt();
	m = endTemp[1].toInt()-beginTemp[1].toInt();
	if (m<0 && h>0)
	{
		h -= 1;
		m += 60;
	}
	timeTemp1.setNum(h);
	timeTemp2.setNum(m);

	//QMessageBox::critical(0,"错误", "开始时间\n" + temp1[1] + "\n结束时间\n" + temp2[1]);
*/
	QSqlQuery query;
	query.prepare("INSERT INTO teach_info(coach_id, teach_date_start, teach_date_end, teach_row_id, teach_stu_num) "
		"VALUES (:coach_id, :teach_date, :teach_timestamp, :teach_row_id, :teach_stu_num)");
	query.bindValue(":coach_id", coachId);
	query.bindValue(":teach_date_start", teachStart.toString("yyyy-MM-dd hh:mm"));
	query.bindValue(":teach_date_end", teachEnd.toString("yyyy-MM-dd hh:mm"));
	query.bindValue(":teach_row_id", rowId);
	query.bindValue(":teach_stu_num", teachStuNum);

	if (!query.exec())
		QMessageBox::critical(NULL, "错误", "录入授课信息失败!\n" + query.lastError().text());
	else
		QMessageBox::information(NULL, "正确", "录入授课信息成功!", QMessageBox::Ok, QMessageBox::Ok);

	this->hide();
	//QSqlQuery querySelect("SELECT coach_id FROM coach WHERE coach_name=")
}


void AddTeachInfo::setRow(const int rowId)
{
	QString id;
	id.setNum(rowId);
	ui.comboBoxTeachRow->addItem(id);
}

void AddTeachInfo::setCoachInfo(const QString& name/* = */)
{
	QSqlQuery query;
	query.prepare("SELECT coach_id FROM coach WHERE coach_name=\'" + name + "\'");
	query.exec();
	if (query.next())
		coachId = query.value(0).toString();
	else
		QMessageBox::critical(NULL, "错误", "教练姓名错误!\n" + query.lastError().text());
	coachName = name;
}

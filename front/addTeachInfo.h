#ifndef _ADD_TEACH_INFO_H
#define _ADD_TEACH_INFO_H
#include <QDialog>
#include <QSqlQuery>
#include "ui_addTeachInfo.h"

class AddTeachInfo : public QDialog
{
	Q_OBJECT

public:
	AddTeachInfo(QDialog *parent = 0);
	~AddTeachInfo();
	void setRow(const int id);
	void setCoachInfo(const QString& name);
	private slots:
		void add();

private:
	Ui::AddTeachInfoUI ui;
	QString rowId;
	QString teachStuNum;
	QString timeStamp;
	QString coachId;
	QString coachName;
};
#endif
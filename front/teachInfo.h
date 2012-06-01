#ifndef _TEACH_INFO_H
#define _TEACH_INFO_H
#include "ui_teachInfo.h"
#include <QDialog>
#include <QSqlQuery>

class TeachInfo : public QDialog
{
	Q_OBJECT
public:
	TeachInfo(QDialog *parent = 0);
	~TeachInfo();
	void setCoach(const QString& name);
	public slots:
		void showTeachInfo();
private:
	Ui::TeachInfoUI ui;
	QSqlQuery query;
	QString coachName;
	QVector<QString> itemText;
	QVector<QTableWidgetItem> item;
	enum{selectProportyNum = 6};
};

#endif

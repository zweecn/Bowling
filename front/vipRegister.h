#ifndef _VIP_REGISTER_H
#define _VIP_REGISTER_H
#include "ui_vipRegister.h"
#include <QSqlTableModel>
#include <QString>
#include <QDialog>
#include <QSqlQuery>

class VipRegister : public QDialog
{
	Q_OBJECT

public:
	VipRegister(QDialog *parent = 0);
	~VipRegister();
	QSqlQuery query;
	private slots:
		void regist();
		//void getVipName();
private:
	Ui::VipRegisterUI ui;
	//QString name;
};

#endif

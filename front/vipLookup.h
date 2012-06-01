#ifndef _VIP_INFO_LOOKUP_H
#define _VIP_INFO_LOOKUP_H
#include <QSqlTableModel>
#include <QString>
#include <QDialog>
#include "ui_vipInfoLookup.h"

class VipLookup : public QDialog
{
	Q_OBJECT

public:
	VipLookup(QDialog *parent = 0);
	~VipLookup();
	QSqlTableModel* model;
	private slots:
		void prepareModel();
		//void getVipName();
private:
	Ui::VipInfoLookupUI ui;
	//QString name;
};

#endif
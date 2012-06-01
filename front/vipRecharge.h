#ifndef _VIP_RECHARGE_H
#define _VIP_RECHARGE_H
#include "ui_vipRecharge.h"
#include <QDialog>

class VipRecharge : public QDialog
{
	Q_OBJECT

public:
	VipRecharge(QDialog *parent = 0);
	~VipRecharge();
	QString money;
	private slots:
		void updateMoney();
		void showMessage();
private:
	Ui::VipRechargeUI ui;
	//QString name;
};

#endif
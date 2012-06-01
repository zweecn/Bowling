#include "vipRecharge.h"
#include <QSqlTableModel>
#include <QMessageBox>

VipRecharge::VipRecharge(QDialog *parent) : QDialog(parent)
{
	ui.setupUi(this);
	money.clear();
	QObject::connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(updateMoney()));
	//QObject::connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
}

VipRecharge::~VipRecharge()
{

}

void VipRecharge::showMessage()
{
	QMessageBox::critical(0, "²âÊÔÐÅºÅ", "²âÊÔÒ»ÏÂ");
}

void VipRecharge::updateMoney()
{
	money = ui.lineEditMoney->text();
	this->hide();
}

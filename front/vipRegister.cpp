#include "vipRegister.h"
#include <QDate>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>

VipRegister::VipRegister(QDialog *parent /* = 0 */) : QDialog(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.pushButtonRegister, SIGNAL(clicked()), this, SLOT(regist()));
	//QObject::connect(ui.pushButtonRegister, SIGNAL(clicked()), this, SLOT(close()));
}

VipRegister::~VipRegister()
{

}

void VipRegister::regist()
{
	QString name = ui.lineEditName->text();
	QString cardId = ui.lineEditCardId->text();
	QString phone = ui.lineEditPhone->text();
	QString money = ui.lineEditBalance->text();

	QString sex = ui.comboBoxSex->currentText();
	QString type = ui.comboBoxType->currentText();
/*
	QSqlTableModel* modelCheck = new QSqlTableModel;
	modelCheck->setTable("vip");
	QString filter("vip_cardid=\'"+cardId+'\'');
	modelCheck->setFilter(filter);
	modelCheck->select();
	if (modelCheck->rowCount()>0)
	{

	}
*/
	QSqlQuery queryCheck("SELECT * FROM vip WHERE vip_cardid=\'"+cardId+"\'" + " AND " + "vip_name=\'" + name + "\'");
	queryCheck.exec();
	if (queryCheck.next())
	{
		QMessageBox::critical(NULL, "错误", "已存在此会员,不能重复注册!");
	}
	else
	{
		QString msg;
		msg = "姓名:\t" + name + "\n性别:\t" + sex + "\n身份证号:\t" + cardId + "\n电话:\t" + phone + "\n优惠方式:\t" + type + "\n预存费用:\t" + money;

		int ret = QMessageBox::question(this, tr("注册确认"), "确认注册?\n" + msg,
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		switch (ret) 
		{
		   case QMessageBox::Yes:
			   query.prepare("INSERT INTO vip(vip_name, vip_sex, vip_cardid, vip_phone, vip_login_date, vip_type, vip_balance) "
				   "VALUES (:vip_name, :vip_sex, :vip_cardid, :vip_phone, :vip_login_date, :vip_type, :vip_balance)");

			   query.bindValue(":vip_name", name);
			   query.bindValue(":vip_sex", sex);
			   query.bindValue(":vip_cardid", cardId);
			   query.bindValue(":vip_phone", phone);
			   query.bindValue(":vip_login_date", QDate::currentDate().toString("yyyy-MM-dd"));
			   query.bindValue(":vip_type", type.toInt());
			   query.bindValue(":vip_balance", money.toDouble());
			   break;
		   case QMessageBox::No:
			   // Don't Save was clicked
			   break;
		   default:
			   // should never be reached
			   break;
		}

		this->hide();
	}
}

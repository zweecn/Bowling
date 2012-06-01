#include "detailrule.h"
#include <QtSql>

BusiRule::BusiRule(QDialog *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
	QObject::connect(ui.okPushButton, SIGNAL(clicked()), this, SLOT(updateDetailRule()));
	week = "1";
}

void BusiRule::updateDetailRule()
{
	if (ui.morningStartDateTimeEdit->time() >= ui.morningEndDateTimeEdit->time() ||
		ui.afternoonStartDateTimeEdit->time() >= ui.afternoonEndDateTimeEdit->time() ||
		ui.eveningStartDateTimeEdit->time() >= ui.eveningEndDateTimeEdit->time() ||
		ui.morningEndDateTimeEdit->time() > ui.afternoonStartDateTimeEdit->time() ||
		ui.afternoonEndDateTimeEdit->time() > ui.eveningStartDateTimeEdit->time())
	{
		QMessageBox::critical(0, tr("´íÎó"), tr("Ê±¶ÎÉèÖÃ³åÍ»!"));
		return;
	}
	QString updateSqlModel = "UPDATE business_rule SET busi_starttime = '%1', busi_endtime = '%2', busi_price = %3 WHERE busi_week = %4 AND busi_duration = %5;";
	QString tempSql = updateSqlModel;
	QSqlQuery sql(tempSql.arg(ui.morningStartDateTimeEdit->time().toString("h:m:s")).arg(ui.morningEndDateTimeEdit->time().toString("h:m:s")).arg(ui.morningPriceLineEdit->text()).arg(week).arg("1"));
	sql.exec();

	tempSql = updateSqlModel;
	sql.clear();
	sql = tempSql.arg(ui.afternoonStartDateTimeEdit->time().toString("h:m:s")).arg(ui.afternoonEndDateTimeEdit->time().toString("h:m:s")).arg(ui.afternoonPriceLineEdit->text()).arg(week).arg("2");
	sql.exec();

	tempSql = updateSqlModel;
	sql.clear();
	sql = tempSql.arg(ui.eveningStartDateTimeEdit->time().toString("h:m:s")).arg(ui.eveningEndDateTimeEdit->time().toString("h:m:s")).arg(ui.eveningPriceLineEdit->text()).arg(week).arg("3");
	sql.exec();

	accept();
}

void BusiRule::init(ruleData initData)
{
	this->week = initData.week;
	this->ui.morningStartDateTimeEdit->setDateTime(initData.morningStart);
	this->ui.morningEndDateTimeEdit->setDateTime(initData.morningEnd);
	this->ui.morningPriceLineEdit->setText(initData.morningPrice);

	this->ui.afternoonStartDateTimeEdit->setDateTime(initData.afternoonStart);
	this->ui.afternoonEndDateTimeEdit->setDateTime(initData.afternoonEnd);
	this->ui.afternoonPriceLineEdit->setText(initData.afternoonPrice);

	this->ui.eveningStartDateTimeEdit->setDateTime(initData.eveningStart);
	this->ui.eveningEndDateTimeEdit->setDateTime(initData.eveningEnd);
	this->ui.eveningPriceLineEdit->setText(initData.eveningPrice);
}

BusiRule::~BusiRule()
{

}
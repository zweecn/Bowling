#include "atm.h"
#include <QtSql>
#include <QtGui>

ATM::ATM(QDialog *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
	atmUI.setupUi(this);
	QObject::connect(atmUI.okPushButton, SIGNAL(clicked()), this, SLOT(doShowHistory()));
}

void ATM::doShowHistory()
{
	QSqlQuery sql;
	sql.prepare("SELECT AVG(vip_score), SUM(vip_x_count), SUM(vip_hx_count) FROM score_record WHERE vip_id = ?;");
	sql.addBindValue(atmUI.vipLineEdit->text());
	sql.exec();
	if (!sql.size())
	{
		QMessageBox::information(0, "结果", tr("无历史记录"));
		return;
	}
	sql.next();
	atmUI.atmAvgScore->setText(sql.value(0).toString());
	atmUI.atmHitAllCount->setText(sql.value(1).toString());
	atmUI.atmCompleteCount->setText(sql.value(2).toString());
}

ATM::~ATM()
{

}
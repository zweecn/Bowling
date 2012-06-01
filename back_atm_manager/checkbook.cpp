#include "checkbook.h"

checkBook::checkBook(QDialog *parent, Qt::WFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
	model = new QSqlTableModel;
	model->setTable("book_record");
	ui.bookTimeDateEdit->setMinimumDate(QDate::currentDate());
	ui.bookTimeDateEdit->setDate(QDate::currentDate());
	QObject::connect(ui.okPushButton, SIGNAL(clicked()), this, SLOT(doCheck()));
}

bool checkBook::lookup(int vipID, QDate date)
{
	QString sVipID;
	sVipID.setNum(vipID);
	QDateTime low(date);
	QDateTime up = low.addDays(1);
	QString filter = "vip_id = " + sVipID + " AND book_date >= '" + low.toString("yyyy-MM-dd h:m:s") + "' AND book_date <= '" + up.toString("yyyy-MM-dd h:m:s") + "';";
	model->setFilter(filter);
	return model->select();
}

void checkBook::doCheck()
{
	if (!lookup(ui.vipLineEdit->text().toInt(), ui.bookTimeDateEdit->date()))
	{
		QMessageBox::critical(0, QObject::tr("Error"),	QObject::tr("Check Error!"));
	}
	this->hide();
}

checkBook::~checkBook()
{
	delete model;
}
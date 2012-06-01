#include"front_check_book.h"

FrontCheckBook::FrontCheckBook(QDialog *parent, Qt::WFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
	ui.bookTimeDateEdit->setDisabled(true);
	model = new QSqlTableModel;
	model->setTable("book_record");
	ui.bookTimeDateEdit->setMinimumDate(QDate::currentDate());
	ui.bookTimeDateEdit->setDate(QDate::currentDate());
	
	QObject::connect(ui.checkBoxDate, SIGNAL(toggled(bool)), this, SLOT(dateCheckBoxChange(bool)));
	QObject::connect(ui.okPushButton, SIGNAL(clicked()), this, SLOT(lookup()));
}

void FrontCheckBook::lookup()
{
	QString sVipID;
	if (ui.vipLineEdit->text()!="")
		sVipID.setNum(ui.vipLineEdit->text().toInt());
	QDateTime low(ui.bookTimeDateEdit->date());
	QDateTime up = low.addDays(1);
	QString filter;
        //bool hasDate = ui.checkBoxDate->isChecked();
	
	if (ui.checkBoxDate->isChecked() && sVipID!="")
	{
		 filter = "vip_id = " + sVipID + " AND book_date >= '" + low.toString("yyyy-MM-dd h:m:s") + "' AND book_date <= '" + up.toString("yyyy-MM-dd h:m:s") + "';";
		 model->setFilter(filter);
	}
	else if ((!ui.checkBoxDate->isChecked()) && sVipID!="")
	{
		filter = "vip_id=" + sVipID;
		model->setFilter(filter);
	}
	else if (ui.checkBoxDate->isChecked() && sVipID=="")
	{
		filter = "book_date >= '" + low.toString("yyyy-MM-dd h:m:s") + "' AND book_date <= '" + up.toString("yyyy-MM-dd h:m:s") + "';";
		model->setFilter(filter);
	}
	
	//return model->select();	
	this->hide();
}

//void FrontCheckBook::doCheck()
//{
//	if (!lookup())
//	{
//		QMessageBox::critical(0, QObject::tr("Error"),	QObject::tr("Check Error!"));
//	}
//	
//}


void FrontCheckBook::dateCheckBoxChange(bool checked)
{
	ui.bookTimeDateEdit->setEnabled(checked);
}

FrontCheckBook::~FrontCheckBook()
{
	delete model;
}

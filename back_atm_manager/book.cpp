#include "book.h"

book::book(QDialog *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
	ui.setupUi(this);
	QObject::connect(ui.okPushButton, SIGNAL(clicked()), this, SLOT(addBook()));
}

bool book::reverse(int vipID, QDateTime bookTime, int bookRow)
{
	QSqlQuery sql;
	if (!isValid(vipID) || rowIsOccupied(bookRow, bookTime))//等VIP好了以后测试
		return false;
	sql.prepare("INSERT INTO book_record VALUES (NULL, ?, ?, ?);");
	sql.addBindValue(vipID);
	sql.addBindValue(bookTime.toString("yyyy-MM-dd h:m:s"));
	sql.addBindValue(bookRow);
	return sql.exec();
}

bool book::rowIsOccupied(int bookRow, QDateTime bookTime)
{
	QSqlQuery sql;
	QDateTime low = QDateTime::currentDateTime();
	QDateTime up = low.addSecs(3600);
	if (bookTime <= low && bookTime > up)
		return false;
	sql.prepare("SELECT FROM book_record WHERE book_row = ? AND book_date > ? AND book_date <= ?");
	sql.addBindValue(bookRow);
	sql.addBindValue(low.toString("yyyy-MM-dd h:m:s"));
	sql.addBindValue(up.toString("yyyy-MM-dd h:m:s"));
	return sql.exec();
}

bool book::isValid(int vipID)
{
	QSqlQuery sql;
	QString sVipID;
	sVipID.setNum(vipID);
	sql.prepare("SELECT vip_id FROM vip WHERE vip_id = " + sVipID);
	sql.exec();
	return sql.size();
}


bool book::addBook()
{
	this->hide();
	return reverse(ui.vipLineEdit->text().toInt(), ui.bookTimeDateTimeEdit->dateTime(), ui.rowComboBox->currentText().toInt());
}

void book::initDate()
{
	QDateTime current = QDateTime::currentDateTime();
	ui.bookTimeDateTimeEdit->setDateTime(current);
	ui.bookTimeDateTimeEdit->setMinimumDateTime(current);

	QSqlQuery sql;
	sql.prepare("SELECT row_id FROM row;");
	sql.exec();
	QStringList rowList;
	while (sql.next())
	{
		rowList.push_back(sql.value(0).toString());
	}
	ui.rowComboBox->clear();
	ui.rowComboBox->addItems(rowList);
}

book::~book()
{

}

#ifndef BOOK_H
#define BOOK_H

#include "ui_book.h"
#include <QtGui>
#include <QString>
#include <QDateTime>
#include <QtSql>

class book : public QDialog
{
	Q_OBJECT

public:
	book(QDialog *parent = 0, Qt::WFlags flags = 0);
	void initDate();
	~book();
private slots:
	bool addBook();
private:
	Ui::bookUI ui;
	bool reverse(int vipID, QDateTime bookTime, int bookRow);
        bool rowIsOccupied(int bookRow, QDateTime bookTime);
        bool isValid(int vipID);
};

#endif

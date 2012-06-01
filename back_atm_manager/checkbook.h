#ifndef CHECKBOOK_H
#define CHECKBOOK_H

#include "ui_checkBook.h"
#include <QtGui>
#include <QString>
#include <QDateTime>
#include <QtSql>

class checkBook : public QDialog
{
	Q_OBJECT

public:
	checkBook(QDialog *parent = 0, Qt::WFlags flags = 0);
	~checkBook();
	QSqlTableModel *model;
private slots:
	void doCheck();
private:
	Ui::checkBook ui;
	bool lookup(int vipID, QDate date);
};

#endif
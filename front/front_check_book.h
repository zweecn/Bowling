#ifndef _FRONT_CHECK_BOOK_H
#define _FRONT_CHECK_BOOK_H

#include "ui_front_checkbook.h"
#include <QtGui>
#include <QString>
#include <QDateTime>
#include <QtSql>

class FrontCheckBook : public QDialog
{
	Q_OBJECT

public:
    FrontCheckBook(QDialog *parent = 0, Qt::WFlags flags = 0);
    ~FrontCheckBook();
	QSqlTableModel *model;
private slots:
	//void doCheck();
	void lookup();
	void dateCheckBoxChange(bool checked);
private:
    Ui::front_checkBook ui;
	
};

#endif

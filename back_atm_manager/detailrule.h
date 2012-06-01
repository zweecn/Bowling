#ifndef DETAILRULE_H
#define DETAILRULE_H

#include "ui_detailRule.h"
#include <QtGui>

class ruleData
{
public:
	QString week;
	QDateTime morningStart;
	QDateTime morningEnd;
	QString morningPrice;

	QDateTime afternoonStart;
	QDateTime afternoonEnd;
	QString afternoonPrice;

	QDateTime eveningStart;
	QDateTime eveningEnd;
	QString eveningPrice;
};

class BusiRule : public QDialog
{
	Q_OBJECT

public:
	BusiRule(QDialog *parent = 0, Qt::WindowFlags flags = 0);
	void init(ruleData data);
	~BusiRule();
public slots:
	void updateDetailRule();
private:
	QString week;
	Ui::busiDetailRule ui;
};

#endif
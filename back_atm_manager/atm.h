#ifndef ATM_H
#define ATM_H

#include "ui_ATM.h"
#include <QDialog>

class ATM : public QDialog
{
	Q_OBJECT

public:
	ATM(QDialog *parent = 0, Qt::WindowFlags flags = 0);
	~ATM();
private slots:
	void doShowHistory();
private:
	Ui::atm atmUI;
};
#endif
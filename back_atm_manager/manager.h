#ifndef MANAGER_H
#define MANAGER_H

#include "ui_manager.h"
#include <QtGui>
#include <QtSql>

class Manager : public QDialog
{
	Q_OBJECT

public:
	Manager(QDialog * parent = 0, Qt::WindowFlags flags = 0);
	~Manager();
private slots:
	void doInsEmp();
	void doDelEmp();
	void doCheckEmp();
	void showTable(int index);
private:
	QSqlTableModel *employeeModel;
	QSqlQueryModel *financeModel;
	Ui::managerAdmin managerUI;
	void showAllEmp();
	void showAllFinance();
};

#endif
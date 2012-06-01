#include "manager.h"

Manager::Manager(QDialog * parent /* = 0 */, Qt::WindowFlags flags /* = 0 */)
: QDialog (parent, flags)
{
	setWindowFlags(Qt::WindowMinMaxButtonsHint);
	managerUI.setupUi(this);
	managerUI.empTableView->setSortingEnabled(true);
	managerUI.financeTableView->setSortingEnabled(true);
	employeeModel = new QSqlTableModel;
	employeeModel->setTable("employee");
	employeeModel->setHeaderData(1, Qt::Horizontal, "姓名");
	employeeModel->setHeaderData(2, Qt::Horizontal, "性别");
	employeeModel->setHeaderData(3, Qt::Horizontal, "年龄");
	employeeModel->setHeaderData(4, Qt::Horizontal, "职位");
	employeeModel->setHeaderData(5, Qt::Horizontal, "联系方式");
	employeeModel->setHeaderData(6, Qt::Horizontal, "工资");

	financeModel = new QSqlQueryModel;
	financeModel->setQuery("SELECT f_id, f_date, f_type, f_money, employee_name, f_use FROM finance, employee WHERE employee_id = f_employee_id;");
	financeModel->setHeaderData(1, Qt::Horizontal, "");

	financeModel->setHeaderData(0, Qt::Horizontal, "编号");
	financeModel->setHeaderData(1, Qt::Horizontal, "日期");
	financeModel->setHeaderData(2, Qt::Horizontal, "收入/支出");
	financeModel->setHeaderData(3, Qt::Horizontal, "金额");
	financeModel->setHeaderData(4, Qt::Horizontal, "经手人");
	financeModel->setHeaderData(5, Qt::Horizontal, "附注");

	QObject::connect(managerUI.managerTab, SIGNAL(currentChanged(int)), this, SLOT(showTable(int)));
	QObject::connect(managerUI.empCheckPushButton, SIGNAL(clicked()), this, SLOT(doCheckEmp()));
	QObject::connect(managerUI.empInsPushButton, SIGNAL(clicked()), this, SLOT(doInsEmp()));
	QObject::connect(managerUI.empDelPushButton, SIGNAL(clicked()), this, SLOT(doDelEmp()));

	showAllEmp();
}

void Manager::showTable(int index)
{
	switch (index)
	{
	case 0:
		showAllEmp();
		break;
	case 1:
		showAllFinance();
		break;
	}
}

void Manager::showAllFinance()
{
	managerUI.financeTableView->setModel(financeModel);
	managerUI.financeTableView->show();
}

void Manager::showAllEmp()
{
	employeeModel->select();
	managerUI.empTableView->setModel(employeeModel);
	managerUI.empTableView->hideColumn(0);
	managerUI.empTableView->show();
}

void Manager::doCheckEmp()
{
	if (managerUI.empNameLineEdit->text() != "")
	{
		QString filter = "employee_name = '%1'";
		employeeModel->setFilter(filter.arg(managerUI.empNameLineEdit->text()));
		employeeModel->select();
		managerUI.empTableView->show();
	}
	else
	{
		employeeModel->setFilter("");
		employeeModel->select();
		managerUI.empTableView->show();
	}
}

void Manager::doInsEmp()
{
	QAbstractItemModel *model = managerUI.empTableView->model();
	model->insertRow(model->rowCount());
}

void Manager::doDelEmp()
{
	QModelIndex cur = managerUI.empTableView->currentIndex();
	QString id = managerUI.empTableView->model()->index(cur.row(), 0).data().toString();
	QSqlQuery sql;
	sql.prepare("DELETE FROM employee WHERE employee_id = ?;");
	sql.addBindValue(id);
	if (!sql.exec())
	{
		QMessageBox::critical(0, "失败", sql.lastError().text());
		return;
	}
	employeeModel->select();
	managerUI.empTableView->show();
}


Manager::~Manager()
{
	delete employeeModel;
}
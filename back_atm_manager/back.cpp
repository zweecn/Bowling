#include "back.h"
#include <QtSql>

Back::Back(QDialog *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
	setWindowFlags(Qt::WindowMinMaxButtonsHint);
	ui.setupUi(this);
	ui.goodsDateEdit->setEnabled(false);
	ui.goodsTypeComboBox->setEnabled(false);

	ui.awardTableView->setSortingEnabled(true);
	ui.bookTableView->setSortingEnabled(true);
	ui.coachTableView->setSortingEnabled(true);
	ui.equipTableView->setSortingEnabled(true);
	ui.goodsDetailTableView->setSortingEnabled(true);
	ui.goodsTotalTableView->setSortingEnabled(true);

	QObject::connect(ui.registerPushButton, SIGNAL(clicked()), this, SLOT(showRegisterUI()));
	QObject::connect(ui.checkBookPushButton, SIGNAL(clicked()), this, SLOT(showCheckUI()));
	QObject::connect(ui.cancelBookPushButton, SIGNAL(clicked()), this, SLOT(cancelBook()));
	QObject::connect(ui.newCoachPushButton, SIGNAL(clicked()), this, SLOT(showNewCoachUI()));
	QObject::connect(ui.backTab, SIGNAL(currentChanged(int)), this, SLOT(showCoachTable(int)));
	QObject::connect(ui.goodsDateCheckBox, SIGNAL(toggled(bool)), this, SLOT(setDateEnabled(bool)));
	QObject::connect(ui.goodsTypeCheckBox, SIGNAL(toggled(bool)), this, SLOT(setTypeEnabled(bool)));
	QObject::connect(ui.goodsChildTab, SIGNAL(currentChanged(int)), this, SLOT(showStoreGoodsTable(int)));
	QObject::connect(ui.checkGoodsPushButton, SIGNAL(clicked()), this, SLOT(doCheckGoods()));
	QObject::connect(ui.newGoodsOkPushButton, SIGNAL(clicked()), this, SLOT(doAddGoodsRecord()));
	QObject::connect(ui.goodsChildTab, SIGNAL(currentChanged(int)), this, SLOT(showCoachTable(int)));//BUG
	QObject::connect(ui.awardAddPushButton, SIGNAL(clicked()), this, SLOT(doAddAwardRule()));
	QObject::connect(ui.awardDeletePushButton, SIGNAL(clicked()), this, SLOT(doDeleteAwardRule()));
	QObject::connect(ui.dumpBrowsePushButton, SIGNAL(clicked()), this, SLOT(doBrowseSaveFile()));
	QObject::connect(ui.restoreBrowsePushButton, SIGNAL(clicked()), this, SLOT(doBrowseOpenFile()));
	QObject::connect(ui.dumpPushButton, SIGNAL(clicked()), this, SLOT(doDump()));
	QObject::connect(ui.restorePushButton, SIGNAL(clicked()), this, SLOT(doRestore()));
	QObject::connect(ui.monPushButton, SIGNAL(clicked()), this, SLOT(showMonDetail()));
	QObject::connect(ui.tuePushButton, SIGNAL(clicked()), this, SLOT(showTueDetail()));
	QObject::connect(ui.wedPushButton, SIGNAL(clicked()), this, SLOT(showWedDetail()));
	QObject::connect(ui.thuPushButton, SIGNAL(clicked()), this, SLOT(showThuDetail()));
	QObject::connect(ui.friPushButton, SIGNAL(clicked()), this, SLOT(showFriDetail()));
	QObject::connect(ui.satPushButton, SIGNAL(clicked()), this, SLOT(showSatDetail()));
	QObject::connect(ui.sunPushButton, SIGNAL(clicked()), this, SLOT(showSunDetail()));
	QObject::connect(ui.fixPushButton, SIGNAL(clicked()), this, SLOT(doFixEquip()));

	coachModel = new QSqlTableModel;
	coachModel->setTable("coach");
	coachModel->setHeaderData(1, Qt::Horizontal, "姓名");
	coachModel->setHeaderData(2, Qt::Horizontal, "性别");
	coachModel->setHeaderData(3, Qt::Horizontal, "联系方式");

	goodsModel = new QSqlTableModel;
	goodsModel->setTable("goods");
	goodsModel->setHeaderData(1, Qt::Horizontal, "货物名称");
	goodsModel->setHeaderData(2, Qt::Horizontal, "售价");
	goodsModel->setHeaderData(3, Qt::Horizontal, "库存数量");
	goodsModel->setHeaderData(4, Qt::Horizontal, "附注");

	recordModel = new QSqlQueryModel;
	recordModel->setQuery("SELECT gr_id, goods_name, gr_date, gr_count, employee_name, agent_name, gr_item_id, gr_type, g_type FROM employee, goods_record, agent, goods WHERE agent_id = gr_agent_id AND employee_id = gr_employee_id AND goods_id = gr_goods_id;");
	recordModel->setHeaderData(1, Qt::Horizontal, "货物名称");
	recordModel->setHeaderData(2, Qt::Horizontal, "日期");
	recordModel->setHeaderData(3, Qt::Horizontal, "金额");
    recordModel->setHeaderData(4, Qt::Horizontal, "经手人");
    recordModel->setHeaderData(5, Qt::Horizontal, "数量");
	recordModel->setHeaderData(6, Qt::Horizontal, "供货商");
	recordModel->setHeaderData(7, Qt::Horizontal, "货物单号");
	recordModel->setHeaderData(8, Qt::Horizontal, "类型");
	recordModel->setHeaderData(9, Qt::Horizontal, "货物类型");

	awardModel = new QSqlTableModel;
	awardModel->setTable("award_rule");
	awardModel->setHeaderData(1, Qt::Horizontal, "幸运分");
	awardModel->setHeaderData(2, Qt::Horizontal, "奖励局数");

	equipModel = new QSqlTableModel;
	equipModel->setTable("row");
	equipModel->setHeaderData(0, Qt::Horizontal, "球道编号");
	equipModel->setHeaderData(1, Qt::Horizontal, "球道状态");
	equipModel->setHeaderData(2, Qt::Horizontal, "球道类型");
	showEquipTable();
}

void Back::setDateEnabled(bool checked)
{
	ui.goodsDateEdit->setEnabled(checked);
}

void Back::setTypeEnabled(bool checked)
{
	ui.goodsTypeComboBox->setEnabled(checked);
}

void Back::showRegisterUI()
{
	registerUI.initDate();
	registerUI.exec();
}

void Back::showCheckUI()
{
	checkUI.exec();
//	checkUI.model->setHeaderData(0, Qt::Horizontal, tr("编号"));
	checkUI.model->setHeaderData(1, Qt::Horizontal, tr("VIP"));
	checkUI.model->setHeaderData(2, Qt::Horizontal, tr("预约时间"));
	checkUI.model->setHeaderData(3, Qt::Horizontal, tr("预约球道"));
	ui.bookTableView->setModel(checkUI.model);
	ui.bookTableView->hideColumn(0);
	ui.bookTableView->show();
}

void Back::showNewCoachUI()
{
	newCoachUI.exec();
	showCoachTable(2);
}

bool Back::cancelBook()
{
	QModelIndex cur = ui.bookTableView->currentIndex();
	QAbstractItemModel *model = ui.bookTableView->model();
	return model->removeRow(cur.row());
}

void Back::showEquipTable()
{
	equipModel->setFilter("row_state = '维修'");
	equipModel->select();
	ui.equipTableView->setModel(equipModel);
	ui.equipTableView->show();
}

void Back::showStoreGoodsTable(int newIndex)
{
	if (newIndex != 0)
		return;
	goodsModel->select();
	ui.goodsTotalTableView->setModel(goodsModel);
	ui.goodsTotalTableView->hideColumn(0);
	ui.goodsTotalTableView->show();
}

void Back::showCoachTable(int newIndex)
{
	QStringList empList;
	QStringList agentList;
	switch (newIndex)
	{
	case 0:
		showEquipTable();
		break;
	case 2:
		coachModel->select();
		ui.coachTableView->setModel(coachModel);
		ui.coachTableView->hideColumn(0);
		ui.coachTableView->show();
		break;
	case 3:
		switch (ui.goodsChildTab->currentIndex())
		{
		case 0:
			goodsModel->select();
			ui.goodsTotalTableView->setModel(goodsModel);
			ui.goodsTotalTableView->hideColumn(0);
			ui.goodsTotalTableView->show();
			break;
		case 1:
			break;
		case 2:
			empList = getEmpList();
			agentList = getAgentList();
			ui.newGoodsEmpComboBox->clear();
			ui.newGoodsEmpComboBox->addItems(empList);
			ui.newGoodsSupplyComboBox->clear();
			ui.newGoodsSupplyComboBox->addItems(agentList);
			break;
		}
		break;
	case 4:
		showBusiRule();
		break;
	case 5:
		awardModel->select();
		ui.awardTableView->setModel(awardModel);
		ui.awardTableView->hideColumn(0);
		ui.awardTableView->show();
		break;
	default:
		break;
	}
}

void Back::doAddGoodsRecord()
{
	QSqlQuery sql;
	QVariant goods_id;
	sql.prepare("SELECT goods_id, goods_count FROM goods WHERE goods_name = ?;");
	sql.addBindValue(ui.newGoodsNameLineEdit->text());
	sql.exec();
	if (!sql.size())
	{
		sql.prepare("INSERT INTO goods VALUES (NULL, ?, ?, '');");
		sql.addBindValue(ui.newGoodsNameLineEdit->text());
		sql.addBindValue(ui.newGoodsCountLineEdit->text());
		sql.exec();
		goods_id = sql.lastInsertId();
	}
	else
	{
		sql.next();
		goods_id = sql.value(0);
		QVariant count = sql.value(1);
		QString goods_count;
		goods_count.setNum(count.toInt() + ui.newGoodsCountLineEdit->text().toInt());
		sql.prepare("UPDATE goods SET goods_count = ? WHERE goods_id = ?;");
		sql.addBindValue(goods_count);
		sql.addBindValue(goods_id);
		sql.exec();
	}
	sql.prepare("SELECT employee_id FROM employee WHERE employee_name = ?;");
	sql.addBindValue(ui.newGoodsEmpComboBox->currentText());
	if (!sql.exec())
		QMessageBox::critical(0, "Failed", sql.lastError().text());
	sql.next();
	QVariant gr_employee_id = sql.value(0);

	sql.prepare("SELECT agent_id FROM agent WHERE agent_name = ?;");
	sql.addBindValue(ui.newGoodsSupplyComboBox->currentText());
	if (!sql.exec())
		QMessageBox::critical(0, "Failed", sql.lastError().text());
	sql.next();
	QVariant gr_agent_id = sql.value(0);

	sql.prepare("INSERT INTO goods_record VALUES (NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	sql.addBindValue(goods_id);
	sql.addBindValue(ui.newGoodsDateDateEdit->date().toString("yyyy-MM-dd"));
	sql.addBindValue(ui.newGoodsPriceLineEdit->text().toDouble());
	sql.addBindValue(ui.newGoodsCountLineEdit->text().toInt());
	sql.addBindValue(gr_employee_id);
	sql.addBindValue(gr_agent_id);
	sql.addBindValue(ui.newGoodsItemNumLineEdit->text());
	sql.addBindValue("1");
	sql.addBindValue(ui.newGoodsTypeComboBox->currentIndex());
	if (!sql.exec())
	{
		QMessageBox::critical(0, "Failed", sql.lastError().text());
	}
	else
	{
		QMessageBox::information(0, "Succeed", tr("商品录入成功"));
	}
}

void Back::doCheckGoods()
{
	QString filter;
	bool gdIsChecked = ui.goodsDateCheckBox->isChecked();
	bool gtIsChecked = ui.goodsTypeCheckBox->isChecked();
	QString g_type = ui.goodsTypeComboBox->currentText();
	QString gr_type = ui.saleOrBuyComboBox->currentText();
	QString sql = "SELECT gr_id, goods_name, gr_date, gr_count, employee_name, agent_name, gr_item_id, gr_type, g_type FROM employee, goods_record, agent, goods WHERE agent_id = gr_agent_id AND employee_id = gr_employee_id AND goods_id = gr_goods_id AND %1;";
	if (ui.saleOrBuyComboBox->currentIndex() == 0)
		if (gdIsChecked)
			if (gtIsChecked)
				filter = "gr_date = '" + ui.goodsDateEdit->date().toString("yyyy-MM-dd") + "' AND g_type = '" + g_type + "'";
			else
				filter = "gr_date = '" + ui.goodsDateEdit->date().toString("yyyy-MM-dd") + "'";
		else
			if (gtIsChecked)
				filter = "g_type = '" + g_type + "'";
			else
				filter = "";
	else
		if (gdIsChecked)
			if (gtIsChecked)
				filter = "gr_type = '" + gr_type + "' AND gr_date = '" + ui.goodsDateEdit->date().toString("yyyy-MM-dd") + "' AND g_type = '" + g_type + "'";
			else
				filter = "gr_type = '" + gr_type + "' AND gr_date = '" + ui.goodsDateEdit->date().toString("yyyy-MM-dd") + "'";
		else
			if (gtIsChecked)
				filter = "gr_type = '" + gr_type + "' AND g_type = '" + g_type + "'";
			else
				filter = "gr_type = '" + gr_type + "'";
	if (filter != "")
		sql = sql.arg(filter);
	else
		sql = "SELECT gr_id, goods_name, gr_date, gr_count, employee_name, agent_name, gr_item_id, gr_type, g_type FROM employee, goods_record, agent, goods WHERE agent_id = gr_agent_id AND employee_id = gr_employee_id AND goods_id = gr_goods_id;";
	recordModel->setQuery(sql);
	ui.goodsDetailTableView->setModel(recordModel);
	ui.goodsDetailTableView->hideColumn(0);
	ui.goodsDetailTableView->show();
}

QStringList Back::getAgentList()
{
	QSqlQuery sql;
	QStringList agentList;
	sql.prepare("SELECT agent_name FROM agent");
	sql.exec();
	while (sql.next())
	{
		agentList.push_back(sql.value(0).toString());
	}
	return agentList;
}

QStringList Back::getEmpList()
{
	QSqlQuery sql;
	QStringList empList;
	sql.prepare("SELECT employee_name FROM employee");
	sql.exec();
	while (sql.next())
	{
		empList.push_back(sql.value(0).toString());
	}
	return empList;
}

void Back::doAddAwardRule()
{
//	qDebug() << ui.awardTableView->editTriggers();
	QAbstractItemModel *model = ui.awardTableView->model();
	model->insertRow(model->rowCount());
}

void Back::doDeleteAwardRule()
{
	QModelIndex cur = ui.awardTableView->currentIndex();
	QAbstractItemModel *model = ui.awardTableView->model();
	model->removeRow(cur.row());
}

void Back::doBrowseSaveFile()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("备份到"), ".", tr("SQL 文件 (*.sql)"));
	ui.dumpDatabaseEditLine->setText(fileName);
}

void Back::doBrowseOpenFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("选择备份文件"), ".", tr("SQL 文件 (*.sql)"));
	ui.restoreDatabaseEditLine->setText(fileName);
}

void Back::doFixEquip()
{
	QModelIndex cur = ui.equipTableView->currentIndex();
	QString id = ui.equipTableView->model()->index(cur.row(), 0).data().toString();
	QSqlQuery sql;
	sql.prepare("UPDATE row SET row_state = '空闲' WHERE row_id = ?;");
	sql.addBindValue(id);
	if (sql.exec())
	{
		QMessageBox::information(0, tr("成功"), tr("设备维修成功。"));
		showEquipTable();
	}
	else
	{
		QMessageBox::information(0, tr("失败"), sql.lastError().text());
	}
}

void Back::doDump()
{
	QString path = ui.dumpDatabaseEditLine->text();
	QString dumpCmd = "D:\\MySQL\\bin\\mysqldump.exe -uroot -p123456 -hlocalhost bowling";
	QProcess *proc = new QProcess;
	proc->setStandardOutputFile(path);
	proc->start(dumpCmd);
	proc->waitForFinished();
	if (proc->exitStatus() == QProcess::NormalExit)
 	{
 		QMessageBox::information(0, tr("成功"), tr("数据库备份成功"));
	}
 	else
	{
		QMessageBox::critical(0, tr("失败"), tr("数据库备份失败"));
	}
}

void Back::doRestore()
{
	QString path = ui.restoreDatabaseEditLine->text();
	QString dumpCmd = "D:\\MySQL\\bin\\mysql.exe -uroot -p123456 -hlocalhost bowling";
	QProcess *proc = new QProcess;
	proc->setStandardInputFile(path);
	proc->start(dumpCmd);
	proc->waitForFinished();
	if (proc->exitStatus() == QProcess::NormalExit)
	{
		QMessageBox::information(0, tr("成功"), tr("数据库恢复成功"));
	}
	else
	{
		QMessageBox::critical(0, tr("失败"), tr("数据库恢复失败"));
	}
}

void Back::showBusiRule()
{
	QSqlQuery sql;
	QString ruleModel = "%1：\n"
		"起始时间：%2\n"
		"结束时间：%3\n"
		"单局收费：%4\n\n"
		"%5：\n"
		"起始时间：%6\n"
		"结束时间：%7\n"
		"单局收费：%8\n\n"
		"%9：\n"
		"起始时间：%10\n"
		"结束时间：%11\n"
		"单局收费：%12\n\n";
	QString rule = ruleModel;
	sql.prepare("SELECT * FROM business_rule ORDER BY busi_week ASC, busi_duration ASC, busi_starttime ASC;");
	sql.exec();
	
	sql.next();
	rule = rule.arg("上午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("下午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("晚间场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	ui.monPushButton->setText(rule);
	
	rule = ruleModel;
	sql.next();
	rule = rule.arg("上午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("下午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("晚间场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	ui.tuePushButton->setText(rule);

	rule = ruleModel;
	sql.next();
	rule = rule.arg("上午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("下午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("晚间场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	ui.wedPushButton->setText(rule);

	rule = ruleModel;
	sql.next();
	rule = rule.arg("上午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("下午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("晚间场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	ui.thuPushButton->setText(rule);

	rule = ruleModel;
	sql.next();
	rule = rule.arg("上午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("下午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("晚间场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	ui.friPushButton->setText(rule);

	rule = ruleModel;
	sql.next();
	rule = rule.arg("上午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("下午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("晚间场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	ui.satPushButton->setText(rule);

	rule = ruleModel;
	sql.next();
	rule = rule.arg("上午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("下午场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	sql.next();
	rule = rule.arg("晚间场").arg(sql.value(3).toString()).arg(sql.value(4).toString()).arg(sql.value(2).toString());
	ui.sunPushButton->setText(rule);
}

void Back::showMonDetail()
{
	ruleData data;
	data.week = "1";
	busiRuleUI.init(data);
	busiRuleUI.exec();
	showBusiRule();
}

void Back::showTueDetail()
{
	ruleData data;
	data.week = "2";
	busiRuleUI.init(data);
	busiRuleUI.exec();
	showBusiRule();
}

void Back::showWedDetail()
{
	ruleData data;
	data.week = "3";
	busiRuleUI.init(data);
	busiRuleUI.exec();
	showBusiRule();
}

void Back::showThuDetail()
{
	ruleData data;
	data.week = "4";
	busiRuleUI.init(data);
	busiRuleUI.exec();
	showBusiRule();
}

void Back::showFriDetail()
{
	ruleData data;
	data.week = "5";
	busiRuleUI.init(data);
	busiRuleUI.exec();
	showBusiRule();
}

void Back::showSatDetail()
{
	ruleData data;
	data.week = "6";
	busiRuleUI.init(data);
	busiRuleUI.exec();
	showBusiRule();
}

void Back::showSunDetail()
{
	ruleData data;
	data.week = "7";
	busiRuleUI.init(data);
	busiRuleUI.exec();
	showBusiRule();
}

Back::~Back()
{
	delete coachModel;
	delete goodsModel;
	delete recordModel;
	delete awardModel;
	delete equipModel;
}

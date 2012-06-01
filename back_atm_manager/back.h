#ifndef BACK_H
#define BACK_H

#include "ui_back.h"
#include "book.h"
#include "checkbook.h"
#include "newcoach.h"
#include "detailrule.h"

class Back : public QDialog
{
	Q_OBJECT

public:
	Back(QDialog *parent = 0, Qt::WindowFlags flags = 0);
	~Back();
private slots:
	void showRegisterUI();//bookAdmin
	bool cancelBook();
	void showCheckUI();
	void showCoachTable(int newIndex);
	void showStoreGoodsTable(int newIndex);
	void showNewCoachUI();
	void doCheckGoods();
	void doAddGoodsRecord();
	void setDateEnabled(bool checked);
	void setTypeEnabled(bool checked);
	void doDeleteAwardRule();
	void doAddAwardRule();
	void doBrowseOpenFile();
	void doBrowseSaveFile();
	void doDump();
	void doRestore();
	void showMonDetail();
	void showTueDetail();
	void showWedDetail();
	void showThuDetail();
	void showFriDetail();
	void showSatDetail();
	void showSunDetail();
	void doFixEquip();
private:
	QStringList getEmpList();
	QStringList getAgentList();
	void showEquipTable();
	void showBusiRule();
	Ui::backAdmin ui;
	book registerUI;
	checkBook checkUI;
	NewCoach newCoachUI;
	BusiRule busiRuleUI;
	QSqlTableModel *bookModel;
	QSqlTableModel *coachModel;
	QSqlTableModel *goodsModel;
	QSqlQueryModel *recordModel;
	QSqlTableModel *awardModel;
	QSqlTableModel *equipModel;
};

#endif
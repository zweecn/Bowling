#ifndef _CHANGE_ROW_H
#define _CHANGE_ROW_H
#include <QDialog>
#include "ui_changeRow.h"

class ChangeRow : public QDialog
{
	Q_OBJECT;

public:
	ChangeRow(QDialog * parent = 0);
	~ChangeRow();
	int prevRowId;
	int afterRowId;
	void setRow(const int rowId);
	private slots:
		void change();
private:
	Ui::changeRowUI ui;
};


#endif
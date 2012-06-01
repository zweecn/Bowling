#include "changeRow.h"
#include <QMessageBox>

ChangeRow::ChangeRow(QDialog * parent /* = 0 */) : QDialog(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.pushButtonChange, SIGNAL(clicked()), this, SLOT(change()));
	//QObject::connect(ui.pushButtonChange, SIGNAL(clicked()), this, SLOT(close()));
	
}

ChangeRow::~ChangeRow()
{

}

void ChangeRow::change()
{
	prevRowId = ui.comboBoxPrev->currentText().toInt();
	afterRowId = ui.comboBoxAfter->currentText().toInt();
	QMessageBox::information(NULL, NULL, "¸ü»»³É¹¦", QMessageBox::Ok, QMessageBox::Ok);
	this->hide();
}

void ChangeRow::setRow(const int rowId)
{
	QString id;
	id.setNum(rowId);
	ui.comboBoxPrev->addItem(id);
	ui.comboBoxAfter->addItem(id);
}

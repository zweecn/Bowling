#include "newcoach.h"
#include <QtSql>

NewCoach::NewCoach()
{
	ui.setupUi(this);
	QObject::connect(ui.okPushButton, SIGNAL(clicked()), this, SLOT(addNewCoach()));
}

bool NewCoach::addNewCoach()
{
	QSqlQuery sql;
	sql.prepare("INSERT INTO coach VALUES (NULL, ?, ?, ?);");
	sql.addBindValue(ui.coachNameLineEdit->text());
	sql.addBindValue(ui.coachGenderComboBox->currentText());
	sql.addBindValue(ui.coachContactLineEdit->text());
	if (!sql.exec())
	{
		QMessageBox::critical(0, "Error", sql.lastError().text());
		return false;
	}
	else
	{
		this->hide();
		return true;
	}
}

NewCoach::~NewCoach()
{

}
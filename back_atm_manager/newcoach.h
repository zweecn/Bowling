#ifndef NEWCOACH_H
#define NEWCOACH_H

#include "ui_newCoach.h"
#include <QtGui>

class NewCoach : public QDialog
{
	Q_OBJECT

public:
	NewCoach();
	~NewCoach();
private slots:
	bool addNewCoach();
private:
	Ui::newCoachUI ui;
};

#endif

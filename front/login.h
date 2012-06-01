#ifndef _LOGIN_UI_H
#define _LOGIN_UI_H
#include <QDialog>
#include "login.h"
#include "ui_login.h"

class Login : public QDialog
{
        Q_OBJECT

public:
        enum {NOT_VIP = -1, VIP} customerType;
        enum {IS_TIME, IS_COUNT} playType;
        Login(QDialog *parent=0, Qt::WindowFlags flags = 0);
        ~Login();
        int vipId;
        bool isSuccess;
//	int timeBegin;
        QString rest;
        //void prepareShow(const int rowId);
        QString rowID;
        void setRowID(const QString& id);

private slots:
        void updateTotal();
        void enableHour();
        void enableCount();
        void enableVIP();
		void setXXX();
private:
        Ui::loginUI ui;
};
#endif

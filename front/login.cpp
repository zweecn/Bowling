#include "login.h"
#include <QtGui>

Login::Login(QDialog *parent/* =0 */, Qt::WindowFlags flags /* =0 */)
:QDialog(parent, flags)
{
        isSuccess = false;
        ui.setupUi(this);

        ui.countRadioButton->setChecked(true);
        ui.oneHoueLineEdit->setEnabled(false);
        ui.hoursLineEdit->setEnabled(false);
        ui.vipCheckBox->setChecked(false);
        ui.vipCardLineEdit->setEnabled(false);

        QButtonGroup group;
        group.addButton(ui.timeRadioButton);
        group.addButton(ui.countRadioButton);
        vipId = NOT_VIP;

        QObject::connect(ui.countRadioButton, SIGNAL(clicked()), this, SLOT(enableCount()));
        QObject::connect(ui.timeRadioButton, SIGNAL(clicked()), this, SLOT(enableHour()));
        QObject::connect(ui.vipCheckBox, SIGNAL(clicked()), this, SLOT(enableVIP()));
        QObject::connect(ui.hoursLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateTotal()));
        QObject::connect(ui.oneHoueLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateTotal()));
        QObject::connect(ui.countLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateTotal()));
        QObject::connect(ui.oneTimeLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateTotal()));
		QObject::connect(ui.okButton, SIGNAL(clicked()), this, SLOT(setXXX()));
}

void Login::enableVIP()
{
        ui.vipCardLineEdit->setEnabled(ui.vipCheckBox->checkState());
}

void Login::enableHour()
{
        ui.countLineEdit->setEnabled(false);
        ui.oneTimeLineEdit->setEnabled(false);
        ui.oneHoueLineEdit->setEnabled(true);
        ui.hoursLineEdit->setEnabled(true);
}

void Login::enableCount()
{
        ui.countLineEdit->setEnabled(true);
        ui.oneTimeLineEdit->setEnabled(true);
        ui.oneHoueLineEdit->setEnabled(false);
        ui.hoursLineEdit->setEnabled(false);
}

void Login::updateTotal()
{
        QString total;
        double totalTemp;

        if (ui.countRadioButton->isChecked())
        {
                this->rest = ui.countLineEdit->text();
                totalTemp = this->rest.toDouble()*ui.oneTimeLineEdit->text().toDouble();
                this->playType = IS_COUNT;
        }
        else
        {
                this->rest = ui.hoursLineEdit->text();
                totalTemp = this->rest.toDouble()*ui.oneHoueLineEdit->text().toDouble();
                this->playType = IS_TIME;
        }
        total.setNum(totalTemp);
		ui.totalLabel->setText("ºÏ¼Æ: " +total);
        if (total=="")
        {
            isSuccess = false;
        }
        else
        {
            isSuccess = true;
        }

}

void Login::setRowID(const QString& id)
{
        this->rowID = id;
        ui.rowIdLabel->setText("ÇòµÀ£º" + rowID);
}

void Login::setXXX()
{
        if (ui.vipCheckBox->isChecked())
        {
                this->vipId = ui.vipCardLineEdit->text().toInt();
                this->customerType = VIP;
        }
        else
        {
                this->customerType = NOT_VIP;
        }
        updateTotal();
}

Login::~Login()
{

}

#include "vipLookup.h"

VipLookup::VipLookup(QDialog *parent /* = 0 */) : QDialog(parent)
{
	ui.setupUi(this);
	model = new QSqlTableModel;
	//QObject::connect(ui.lineEditVipName, SIGNAL(textChanged()), this, SLOT(getVipName()));
	QObject::connect(ui.pushButtonLookup, SIGNAL(clicked()), this, SLOT(prepareModel()));
	//QObject::connect(ui.pushButtonLookup, SIGNAL(clicked()), this, SLOT(close()));
}

VipLookup::~VipLookup()
{

}

void VipLookup::prepareModel()
{
	QString id = ui.lineEditVipId->text();
	QString cardId = ui.lineEditVipCardId->text();
	QString name = ui.lineEditVipName->text();
	model->setTable("vip");
	QString filter, filter1, filter2, filter3;
	filter1 = "vip_id=" + id;
	filter2 = "vip_cardid='" + cardId + '\'';
	filter3 = "vip_name='" + name + '\'';

	if (id!="" && cardId!="" && name!="")
		filter = filter1 + " AND " + filter2 + " AND " + filter3;
	else if (id=="" && cardId!="" && name!="")
		filter = filter2 + " AND " + filter3;
	else if (id!="" && cardId=="" && name!="")
		filter = filter1 + " AND " + filter3;
	else if (id!="" && cardId!="" && name=="")
		filter = filter1 + " AND " + filter2;
	else if (id!="" && cardId=="" && name=="")
		filter = filter1;
	else if (id=="" && cardId!="" && name=="")
		filter = filter2;
	else if (id=="" && cardId=="" && name!="")
		filter = filter3;

	model->setFilter(filter);
	this->hide();
}

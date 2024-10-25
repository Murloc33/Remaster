#include "ui_diastatusdescription.h"
#include "diastatusdescription.h"

#include <QDebug>


DiaStatusDescription::DiaStatusDescription(QWidget *parent)
	:QDialog(parent)
	,ui(new Ui::DiaStatusDescription)
{
	ui->setupUi(this);

	connect(ui->cb_description, SIGNAL(currentIndexChanged(int)),
			this, SLOT(slotUpdateLDescription(int)));
}

void DiaStatusDescription::setUpModel(QAbstractItemModel* model)
{
	m_model = model;
	ui->cb_description->setModel(m_model);
}

void DiaStatusDescription::updateModel(int index)
{
	ui->cb_description->setCurrentIndex(index != -1 ? index : 0);
}

void DiaStatusDescription::slotUpdateLDescription(int index)
{
	ui->te_description->setText(ui->cb_description->itemData(index, Qt::WhatsThisRole).toString());
}



#include "ui_diadescription.h"
#include "diadescription.h"

#include <QDebug>


DiaDescription::DiaDescription(QWidget *parent)
	:QDialog(parent)
	,ui(new Ui::DiaDescription)
{
	ui->setupUi(this);

	connect(ui->cb_description, SIGNAL(currentIndexChanged(int)),
			this, SLOT(slotUpdateLDescription(int)));
}

void DiaDescription::setUpModel(CBModel* model)
{
	m_model = model;
	ui->cb_description->setModel(m_model);
}

void DiaDescription::updateModel(int index)
{
	ui->cb_description->setCurrentIndex(index != -1 ? index : 0);
}

void DiaDescription::slotUpdateLDescription(int index)
{
	ui->te_description->setText(ui->cb_description->itemData(index, Qt::WhatsThisRole).toString());
}



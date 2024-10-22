#include "ui_diastatusdescription.h"
#include "diastatusdescription.h"

#include <QDebug>


DiaStatusDescription::DiaStatusDescription(QWidget *parent)
	:QDialog(parent)
	,ui(new Ui::DiaStatusDescription)
{
	ui->setupUi(this);

	connect(ui->cb_description, SIGNAL(QComboBox::highlighted(int index)),
			this, SIGNAL(DiaStatusDescription::slotUpdateLDescription));
}

void DiaStatusDescription::setUpModel(QAbstractItemModel* model)
{
	m_model = model;
	ui->cb_description->setModel(m_model);
}

void DiaStatusDescription::updateModel(int index)
{
	ui->cb_description->setCurrentIndex(index);
}

void DiaStatusDescription::slotUpdateLDescription(int index)
{
	ui->label->setText(QVariant(ui->cb_description->currentData(Qt::WhatsThisRole)).toString());
}



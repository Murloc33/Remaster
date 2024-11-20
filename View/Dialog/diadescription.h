#ifndef DIADESCRIPTION_H
#define DIADESCRIPTION_H

#include <QAbstractItemModel>
#include <QDialog>

#include "../../Model/cbmodel.h"

namespace Ui {
	class DiaDescription;
}


class DiaDescription : public QDialog
{
	Q_OBJECT
public:
	DiaDescription(QWidget *parent = nullptr);
	void setUpModel(CBModel* model);
	void updateModel(int index);

private slots:
	void slotUpdateLDescription(int index);


private:
	Ui::DiaDescription* ui;
	CBModel* m_model;
};

#endif // DIADESCRIPTION_H

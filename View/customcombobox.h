#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include <QComboBox>
#include "../Model/cbmodel.h"

class CustomComboBox : public QComboBox
{
	Q_OBJECT
public:
	CustomComboBox(QWidget *parent);

	void setCBState(bool *cb_state);

private:
	void changeState();

signals:
	void sigChangedState();

private:
	bool *m_cb_state;

};

#endif // CUSTOMCOMBOBOX_H

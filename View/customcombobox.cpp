#include "customcombobox.h"

CustomComboBox::CustomComboBox(QWidget *parent)
	: QComboBox(parent)
{
	connect(this, &CustomComboBox::currentTextChanged,
			[this]() {
				changeState();
				emit sigChangedState();
			});
}

void CustomComboBox::setCBState(bool *cb_state)
{
	m_cb_state = cb_state;
}


void CustomComboBox::changeState()
{
	*m_cb_state = true;
}

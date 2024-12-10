#include "customcheckbox.h"

CustomCheckBox::CustomCheckBox(QWidget *parent)
: QCheckBox(parent)
{

}

void CustomCheckBox::setFilter(Filter filter)
{
	m_filter = filter;
}

void CustomCheckBox::setUp()
{
	if (m_filter.id.size() == 0) {
		setEnabled(true);
		return;
	}
	for (auto curId : m_filter.id) {
		if (curId == m_filter.cb->getCurrentItem().id) {
			setEnabled(true);
			return;
		}
	}
}


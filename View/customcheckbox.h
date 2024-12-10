#ifndef CUSTOMCHECKBOX_H
#define CUSTOMCHECKBOX_H

#include <QCheckBox>

#include "../View/customcombobox.h"

class CustomCheckBox : public QCheckBox
{
public:
	struct Filter {
		CustomComboBox * cb;
		QVector<int64_t> id;
	};
public:
	CustomCheckBox(QWidget *parent);

	void setFilter(Filter filter);

	void setUp();

private:
	Filter m_filter;
};

#endif // CUSTOMCHECKBOX_H

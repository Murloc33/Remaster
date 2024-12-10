#include "customcombobox.h"

#include <QModelIndex>

CustomComboBox::CustomComboBox(QWidget *parent)
	: QComboBox(parent)
{

}

CustomComboBox::~CustomComboBox()
{
	delete m_model;
}

void CustomComboBox::fillCB()
{
	QVector<DBManager::Item> itemVector = DBManager::instance()->getData(m_request);
	QVector<DBManager::Item> filterVector;
	for (int i = 0; i < itemVector.size(); ++i) {
		if (checkFilter(itemVector[i])) {
			if (filterVector.contains(itemVector[i])) {
				continue;
			}
			filterVector.push_back(itemVector[i]);
		}

	}
	if (filterVector.size() == 0) {
		setEnabled(false);
		return;
	}
	m_model->addItems(filterVector);
	setCurrentIndex(-1);
	setEnabled(true);
}

DBManager::Item CustomComboBox::getCurrentItem() const
{
	return m_model->getItem(currentIndex());
}

ResultManager::info CustomComboBox::getInfo()
{
	return m_info;
}

int64_t CustomComboBox::getOptionalId()
{
	return m_optionalId;
}

size_t CustomComboBox::count()
{
	return m_model->count();
}

void CustomComboBox::clear()
{
	m_model->clear();
}

bool CustomComboBox::checkFilter(DBManager::Item curItem)
{
	for (auto filter : m_filters) {
		QString pk = filter->getPK();
		int64_t id = filter->getCurrentItem().id;
		int64_t optionalId = filter->getOptionalId();
		if (optionalId == - 1) {
			if (curItem.baseItemsId[pk] == id) {

				continue;
			} else {
				return false;
			}
		} else {
			if (curItem.baseItemsId[pk] == id || curItem.baseItemsId[pk] == optionalId) {
				continue;
			} else {
				return false;
			}
		}
	}
	return true;
}

void CustomComboBox::setModel(QAbstractItemModel *model)
{
	QComboBox::setModel(model);
	m_model = dynamic_cast<CBModel*>(model);
}

void CustomComboBox::setOptionalId(int64_t optionalId)
{
	m_optionalId = optionalId;
}

void CustomComboBox::setInfo(ResultManager::info info)
{
	m_info = info;
}

void CustomComboBox::setRequest(QString request)
{
	m_request = request;
}

void CustomComboBox::setPK(QString pk)
{
	m_pk = pk;
}

void CustomComboBox::setFilters(QVector<CustomComboBox *> filters)
{
	m_filters = filters;
}

QString CustomComboBox::getPK() const
{
	return m_pk;
}


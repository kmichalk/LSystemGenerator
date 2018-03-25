#include "SettingsTableModel.h"
#include "SettingsManager.h"


SettingsTableModel::SettingsTableModel(SettingsManager * settingsManager):
	settingsManager_(settingsManager),
	rowHeight_(DEFAULT_ROW_HEIGHT),
	nameColumnWidth_(DEFAULT_NAME_COLUMN_WIDTH),
	valueColumnWidth_(DEFAULT_VALUE_COLUMN_WIDTH)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

int SettingsTableModel::rowCount(QModelIndex const & parent) const {
	return settingsManager_->size();
}

///////////////////////////////////////////////////////////////////////////////////////////////

int SettingsTableModel::columnCount(QModelIndex const & parent) const {
	return 2;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QVariant SettingsTableModel::data(QModelIndex const & index, int role) const {
	Setting& setting = settingsManager_->get(index.row());
	switch (role) {
	case Qt::DisplayRole:
		return index.column() == 0 ?
			setting.name :
			setting.toString();
	default:
		return QVariant();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool SettingsTableModel::setData(const QModelIndex & index, const QVariant & value, int role) {
	if (role == Qt::EditRole) {
		int row = index.row();
		if (index.column() == 1 && rowExists(row)) {
			if (value.isValid() && !value.toString().isEmpty()) {
				Setting& s = settingsManager_->get(row);
				if (s.parse(value.toString())) {
					emit editCompleted(settingsManager_->get(index.row()));
					return true;
				}
			}
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QVariant SettingsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QString("parameter");
			case 1:
				return QString("value");
			default:
				return QString();
			}
		}
		else if (orientation == Qt::Vertical) {
			return section;
		}
	}
	return QVariant();
}

///////////////////////////////////////////////////////////////////////////////////////////////

Qt::ItemFlags SettingsTableModel::flags(const QModelIndex & index) const {
	if (index.column() == 1)
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	else
		return Qt::ItemIsEnabled;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int SettingsTableModel::rowHeight() const {
	return rowHeight_;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int SettingsTableModel::nameColumnWidth() const {
	return nameColumnWidth_;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int SettingsTableModel::valueColumnWidth() const {
	return valueColumnWidth_;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void SettingsTableModel::setDimensions(int rowHeight, int nameColumnWidth, int valueColumnWidth) {
	this->rowHeight_ = rowHeight;
	this->nameColumnWidth_ = nameColumnWidth;
	this->valueColumnWidth_ = valueColumnWidth;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int SettingsTableModel::nameColumnNumber() const {
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int SettingsTableModel::valueColumnNumber() const {
	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool SettingsTableModel::rowExists(int rowNumber) const {
	return rowNumber < settingsManager_->size();
}

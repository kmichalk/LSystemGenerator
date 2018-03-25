#pragma once

#include "qtableview.h"

class SettingsManager;

class SettingsTableModel: public QAbstractTableModel
{
	Q_OBJECT;

	SettingsManager* settingsManager_;
	int rowHeight_;
	int nameColumnWidth_;
	int valueColumnWidth_;
	
public:
	static constexpr int DEFAULT_ROW_HEIGHT = 20;
	static constexpr int DEFAULT_NAME_COLUMN_WIDTH = 100;
	static constexpr int DEFAULT_VALUE_COLUMN_WIDTH = 150;

	SettingsTableModel(SettingsManager* settingsManager);
	virtual ~SettingsTableModel() = default;

	virtual int rowCount(QModelIndex const& parent = QModelIndex{}) const override;
	virtual int columnCount(QModelIndex const& parent = QModelIndex{}) const override;
	virtual QVariant data(QModelIndex const &index, int role = Qt::DisplayRole) const override;
	virtual bool setData(const QModelIndex & index, const QVariant & value, int role) override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	virtual Qt::ItemFlags flags(const QModelIndex & index) const override;
	int rowHeight() const;
	int nameColumnWidth() const;
	int valueColumnWidth() const;
	void setDimensions(int rowHeight, int nameColumnWidth, int valueColumnWidth);
	int nameColumnNumber() const;
	int valueColumnNumber() const;
	bool rowExists(int rowNumber) const;

signals:
	void editCompleted(QVariant);
};


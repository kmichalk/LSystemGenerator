#pragma once

#include "qtableview.h"

class SettingsManager;
class SettingsTableModel;

class SettingsEditor: public QTableView
{
	Q_OBJECT;

	SettingsManager* settingsManager;
	SettingsTableModel* model;

	void initializeGeometry();
	void setDefaultOptions();
	void setDefaultStyleSheet();

public:
	static constexpr char const DEFAULT_TITLE[] = "Settings";

	SettingsEditor(QWidget* parent = Q_NULLPTR);
	SettingsEditor(SettingsManager* settingsManager, QWidget* parent  = Q_NULLPTR);
	virtual ~SettingsEditor();
	void setSettingsManager(SettingsManager* settingsManager);
};


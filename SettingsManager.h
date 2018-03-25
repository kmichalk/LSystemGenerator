#pragma once

#include "qmap.h"
#include "Setting.h"
#include "xvector.h"

class SettingsManager
{
	struct Entry
	{
		Setting* setting = nullptr;
		size_t index = 0;
	};

	mutable QMap<QString, Entry> settingsMap;
	mutable x::vector<Setting*> settings;

public:
	SettingsManager();
	SettingsManager(SettingsManager const&) = delete;
	SettingsManager(SettingsManager &&) = delete;
	~SettingsManager();

	Setting& get(size_t index) const;
	Setting& get(QString const& name) const;
	template<class _Type>
	Setting& insert(QString const& name, _Type value);
	size_t size() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template<class _Type>
Setting& SettingsManager::insert(QString const & name, _Type value) {
	Entry& e = settingsMap[name];
	if (e.setting == nullptr) {
		e.setting = new Setting(name, QVariant::Invalid);
		settings.push_back(e.setting);
		e.index = settings.lastpos();
	}
	else {
		delete e.setting;
		e.setting = new Setting(name, QVariant::Invalid);
	}
	*e.setting = QVariant(value);
	return *e.setting;
}

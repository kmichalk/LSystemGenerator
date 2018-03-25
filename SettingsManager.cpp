#include "SettingsManager.h"



SettingsManager::SettingsManager() {
}

///////////////////////////////////////////////////////////////////////////////////////////////

SettingsManager::~SettingsManager() {
	settings.delete_each();
}

///////////////////////////////////////////////////////////////////////////////////////////////

Setting& SettingsManager::get(size_t index) const {
	return *settings[index];
}

Setting& SettingsManager::get(QString const & name) const {
	Entry& e = settingsMap[name];
	if (e.setting == nullptr) {
		e.setting = new Setting(name, QVariant::Invalid);
		settings.push_back(e.setting);
		e.index = settings.lastpos();
	}
	return *e.setting;
}

///////////////////////////////////////////////////////////////////////////////////////////////

size_t SettingsManager::size() const {
	return settingsMap.size();
}

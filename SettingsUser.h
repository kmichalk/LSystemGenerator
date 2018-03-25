#pragma once

#include "xvector.h"
#include "vamacros.h"
#include "SettingReference.h"
#include "SettingsManager.h"

class SettingsManager;

class SettingsUser
{
	static x::vector<SettingsUser*> instances_;

protected:
	x::vector<Setting const*> settings;

public:
	static x::vector<SettingsUser*> const& instances();
	SettingsUser();
	virtual ~SettingsUser();
	virtual void loadSettings(SettingsManager const& settings) abstract;
};


#define _DECLARE_FIELD(_Type, _name, _default) SettingReference<_Type> _name;
#define _LINK_SETTING(_Type, _name, _default) _name.link(settings.get(#_name));
#define _INITIALIZE_SETTING(_Type, _name, _default) settings.insert<_Type>(#_name, _default);

#define SETTINGS(...) \
	APPLY_T(_DECLARE_FIELD, __VA_ARGS__); \
	public: \
		static inline void initializeSettings(SettingsManager& settings) { \
			APPLY_T(_INITIALIZE_SETTING, __VA_ARGS__); \
		} \
		virtual inline void loadSettings(SettingsManager const& settings) override { \
			APPLY_T(_LINK_SETTING, __VA_ARGS__); \
		} \
	private: \
	
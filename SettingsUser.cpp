#include "SettingsUser.h"


x::vector<SettingsUser*> const & SettingsUser::instances() {
	return instances_;
}

///////////////////////////////////////////////////////////////////////////////////////////////

SettingsUser::SettingsUser() {
	instances_.push_back(this);
}

///////////////////////////////////////////////////////////////////////////////////////////////

SettingsUser::~SettingsUser() {
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::vector<SettingsUser*> SettingsUser::instances_ = {};
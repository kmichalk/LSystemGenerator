#pragma once

#include "Setting.h"

class AbstractSettingReference
{
public:
	virtual ~AbstractSettingReference() = default;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template<class _Type>
class SettingReference: public AbstractSettingReference
{
	Setting* ptr;

public:
	SettingReference():
		ptr(nullptr)
	{ }

	SettingReference(Setting* ptr)
		: ptr(ptr) 
	{ }

	SettingReference(Setting& ptr)
		: ptr(&ptr) 
	{ }

	__forceinline void link(Setting* ptr) {
		this->ptr = ptr;
	}

	__forceinline void link(Setting& ptr) {
		this->ptr = &ptr;
	}

	__forceinline _Type const& value() const {
		return ptr->value<_Type>();
	}

	__forceinline operator _Type() const {
		return ptr->value<_Type>();
	}

	__forceinline QString toString() const {
		return ptr->toString();
	}

	__forceinline QString const& name() const {
		return ptr->name;
	}

	__forceinline void operator=(_Type const& value) {
		ptr->setValue(value);
	}
};

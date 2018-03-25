#pragma once

#include "qstring.h"

template<class _Type, class _Func, class _Base>
class CustomAction;

template<class _Type>
class Action
{
public:
	//struct Parameters{};

	virtual ~Action() = default;
	virtual void apply(_Type* obj, void const* parameters = nullptr) const abstract;
	virtual QString getName() const abstract;

	template<class _Base = Action<_Type>, class _Func>
	static CustomAction<_Type, _Func, _Base>* custom(_Func&& func);
};

template<class _Type, class _Func, class _Base>
class CustomAction: public _Base
{
	_Func func;

public:
	CustomAction(_Func func):
		func(func)
	{ }

	virtual void apply(_Type* obj) const override {
		func(obj);
	}
};

template<class _Type>
template<class _Base, class _Func>
__forceinline CustomAction<_Type, _Func, _Base>* Action<_Type>::custom(_Func && func) {
	return new CustomAction<_Type, _Func, _Base>(func);
}

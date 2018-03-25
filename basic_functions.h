#pragma once

#include "Expression.h"

namespace basic
{
	template<class _Type>
	__inline _Type add(_Type a, _Type b) {
		return a + b;
	}
/*
	template<class _Type>
	struct Add
	{
		static Function<_Type, 2>* expr;
	};

	template<class _Type>
	Function<_Type, 2> Add<_Type>::expr = new Function<_Type, 2>(add<_Type>)*/


	template<class _Type>
	__inline _Type mult(_Type a, _Type b) {
		return a * b;
	}

	template<class _Type>
	__inline _Type sub(_Type a, _Type b) {
		return a - b;
	}

	template<class _Type>
	__inline _Type div(_Type a, _Type b) {
		return a / b;
	}
}
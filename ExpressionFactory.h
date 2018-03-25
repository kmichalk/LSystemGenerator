#pragma once

#include "Expression.h"
#include "types.h"

template<class _Type = param_t>
__inline auto expr(_Type value) {
	return new Constant<_Type>(value);
}

template<class _Func, class... _Arg>
__inline auto expr(_Func&& func, _Arg&&... args) {
	return new Function<x::return_type_of_t<_Func>, sizeof...(_Arg)>(func, args...);
}

template<class _Type = param_t>
_inline auto var(char ch) {
	return new Variable<_Type>(ch, size_t(ch-'a'));
}


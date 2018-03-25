#pragma once

#include "Expression.h"
#include "basic_functions.h"
#include <string>

template<class _Type>
class ExpressionParser
{
public:
	virtual ~ExpressionParser() = default;
	//virtual Expression<_Type>* parse(char const* begin) const abstract;
	virtual Expression<_Type>* parse(char const* begin, char delim, size_t(&symbolMap)[256]) const abstract;
};

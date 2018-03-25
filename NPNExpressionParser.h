#pragma once

#include "ExpressionParser.h"


template<class _Type>
class NPNExpressionParser: public ExpressionParser<_Type>
{
	mutable char delim;
	mutable size_t* symbolMap;

	Expression<_Type>* parse_(char const*& ci) const {
		char const* begin = ci;
		while (!x::is_visible(*++ci)){}
		char c = *ci;
		if (c == delim)
			return nullptr;
		switch (c) {
		case '+':
			return new Function<_Type, 2>{
				basic::add<_Type>, parse_(ci), parse_(ci)};
		case '-':
			return new Function<_Type, 2>{
				basic::sub<_Type>, parse_(ci), parse_(ci)};
		case '*':
			return new Function<_Type, 2>{
				basic::mult<_Type>, parse_(ci), parse_(ci)};
		case '/':
			return new Function<_Type, 2>{
				basic::div<_Type>, parse_(ci), parse_(ci)};
		}
		if (x::is_lower(c)) 
			return new Variable<_Type>(c, symbolMap[c]);
		if (x::is_digit(c))
			return new Constant<_Type>(std::strtof(ci, const_cast<char**>(&ci)));
	}

public:
	/*virtual Expression<_Type>* parse(char const* begin) const override {
		return parse_(--begin);
	}*/

	virtual Expression<_Type>* parse(char const* begin, char delim, size_t(&symbolMap)[256]) const override {
		this->delim = delim;
		this->symbolMap = symbolMap;
		return parse_(--begin);
	}
};


#pragma once

#include "types.h"
#include "xvector.h"
#include "Allocator.h"
#include "qtextstream.h"
#include <iostream>
#include "GeometricAction.h"

class Symbol
{
public:
	char ch;
	size_t paramCount;
	param_t* parameters;
	//GeometricAction* action;

	Symbol(char ch);
	//Symbol(char ch, size_t paramCount, param_t* parameters);
	//Symbol(char ch, size_t paramCount);
	////Symbol(char ch, std::initializer_list<param_t> parameters);
	Symbol(char ch, size_t paramCount, Allocator<param_t>* allocator);
	Symbol(Symbol const& other) = default;
	Symbol(Symbol&& other) = default;
	virtual ~Symbol();

	friend std::ostream& operator<<(std::ostream& os, Symbol const& s);
	friend QTextStream& operator<<(QTextStream& qds, Symbol const& s);
};



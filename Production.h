#pragma once

#include "Symbol.h"
#include "xvector.h"
#include "xstring.h"
#include "ParameterBind.h"
#include "Allocator.h"

class GeometricAction;

class Production
{
public:
	struct SymbolExpression
	{
		char ch;
		x::vector<Expression<param_t>*> expressions;

		SymbolExpression(char ch);
		SymbolExpression(char ch, x::vector<Expression<param_t>*>&& expressions);
	};

private:
	x::vector<SymbolExpression> output;
	Allocator<param_t>* parameterAllocator;
	GeometricAction* action;

public:
	Production(x::vector<SymbolExpression> && output, GeometricAction* action = nullptr);
	////Production(x::string const& str);
	////Production(std::initializer_list<SymbolExpression> output);
	virtual ~Production();

	Symbol computeSymbol(Symbol const& predecessor, SymbolExpression const& outExpression) const;	
	virtual void apply(Symbol const& predecessor, x::vector<Symbol>& buffer) const;

	void setParameterAllocator(Allocator<param_t>* allocator);
};



#include "Production.h"



Symbol Production::computeSymbol(Symbol const & predecessor, SymbolExpression const & outExpression) const {
	Symbol outSymbol(outExpression.ch, 
					 outExpression.expressions.size(), 
					 parameterAllocator);		
	if (outExpression.expressions) {
		for (size_t p = 0; p < outSymbol.paramCount; ++p)
			outSymbol.parameters[p] =
				(*outExpression.expressions[p])(predecessor.parameters);
	}
	return outSymbol;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Production::Production(x::vector<SymbolExpression>&& output, GeometricAction* action):
	output(output.move()),
	parameterAllocator(nullptr),
	action(action)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

////Production::Production(x::string const & str):
////	output(str.size())
////{
////	for (char ch : str)
////		output.push_back({ch});
////}

///////////////////////////////////////////////////////////////////////////////////////////////

////Production::Production(std::initializer_list<SymbolExpression> output):
////	output(output)
////{
////}

///////////////////////////////////////////////////////////////////////////////////////////////

void Production::apply(Symbol const & predecessor, x::vector<Symbol>& buffer) const {
	for (auto const& outExpression : output)
		buffer.push_back(std::move(computeSymbol(predecessor, outExpression)));
}

///////////////////////////////////////////////////////////////////////////////////////////////

Production::~Production() {
	for (auto& e : output)
		e.expressions.delete_each();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Production::setParameterAllocator(Allocator<param_t>* allocator) {
	parameterAllocator = allocator;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Production::SymbolExpression::SymbolExpression(char ch):
	ch(ch),
	//paramCount(0),
	expressions(x::NO_ALLOC)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

//Production::SymbolExpression::SymbolExpression(char ch, size_t paramCount):
//	ch(ch),
//	paramCount(paramCount),
//	expressions(NO_ALLOC)
//{
//}

///////////////////////////////////////////////////////////////////////////////////////////////

Production::SymbolExpression::SymbolExpression(char ch, x::vector<Expression<param_t>*>&& expressions):
	ch(ch),
	//paramCount(expressions.size()),
	expressions(expressions.move())
{
}

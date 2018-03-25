#include "Symbol.h"
#include <cstring>

//? is this constructor neccessary? (symbols always initialized by grammar / production)
//Symbol::Symbol(char ch, size_t paramCount):
//	ch(ch),
//	paramCount(paramCount),
//	parameters(paramCount ? new param_t[paramCount] : nullptr)
//{
//}

///////////////////////////////////////////////////////////////////////////////////////////////

Symbol::Symbol(char ch):
	ch(ch),
	paramCount(0),
	parameters(nullptr)
{
}

//Symbol::Symbol(char ch, size_t paramCount, param_t * parameters):
//	ch(ch),
//	paramCount(paramCount),
//	parameters(parameters)
//{
//}

///////////////////////////////////////////////////////////////////////////////////////////////

////? and this
////Symbol::Symbol(char ch, std::initializer_list<param_t> paramList):
////	ch(ch),
////	paramCount(paramCount),
////	parameters(new param_t[paramList.size()])
////{
////	memcpy(parameters, paramList.begin(), paramList.size()*sizeof(param_t));
////}

///////////////////////////////////////////////////////////////////////////////////////////////

Symbol::Symbol(char ch, size_t paramCount, Allocator<param_t>* allocator):
	ch(ch),
	paramCount(paramCount),
	parameters(paramCount ? allocator->alloc(paramCount) : nullptr)
	//action(action)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

//Symbol::Symbol(Symbol && other):
//	ch(other.ch),
//	paramCount(other.paramCount),
//	parameters(other.parameters)
//{
//	other.parameters = nullptr;
//}

///////////////////////////////////////////////////////////////////////////////////////////////

Symbol::~Symbol() {
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::ostream & operator<<(std::ostream & os, Symbol const & s) {
	os<<s.ch;
	if (s.paramCount == 0)
		return os;
	os<<'(';
	x::vector<param_t>(x::ADOPT, s.parameters, s.paramCount).write(os, ", ").discard_data();
	return os<<')';
}

QTextStream & operator<<(QTextStream & qds, Symbol const & s) {
	qds<<s.ch<<'(';
	if (s.paramCount > 0) {
		size_t last = s.paramCount - 1;
		for (size_t i = 0; i<last; ++i)
			qds<<s.parameters[i] << ", ";
		qds<<s.parameters[last];
	}
	return qds<<')';
}

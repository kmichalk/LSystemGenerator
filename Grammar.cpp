#include "Grammar.h"


Allocator<param_t>* Grammar::oldAllocator() const {
	auto prevAllocator = parameterAllocator;
	parameterAllocator = new Pool<param_t>;
	return prevAllocator;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Grammar::Grammar():
	productions{0ull},
	parameterAllocator(new Pool<param_t>),
	geometricActionMap{0ull}
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

//Grammar::Grammar(Grammar const & other):
//	productions{0ull},
//	parameterAllocator(new Pool<param_t>),
//	geometricActionMap{0ull}
//{
//	memcpy(geometricActionMap, other.geometricActionMap, 256*sizeof(GeometricAction*));
//	for (size_t i = 0; i<256; ++i) {
//		if (other.productions[i])
//			setProduction((char)i, new Production(*other.productions[i]));
//	}
//}

///////////////////////////////////////////////////////////////////////////////////////////////

Grammar::~Grammar() {
	for (auto* p : productions)
		delete p;
	delete parameterAllocator;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Grammar::Output* Grammar::produce(unsigned iterations) const {
	x::vector<Symbol> string = axiom;
	x::vector<Symbol> buffer(1000);
	for (auto i = 0; i<iterations; ++i) {
		for (auto const& symbol : string) {
			if (Production* p = productions[symbol.ch]) {
				p->setParameterAllocator(parameterAllocator);
				p->apply(symbol, buffer);
			}
			else
				buffer.push_back(symbol);
		}
		buffer.swap(string).clear();
	}	
	return new Output{string.move(), oldAllocator(), geometricActionMap};
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Grammar::setProduction(char ch, Production * p, GeometricAction* a) {
	productions[ch] = p;
	if (p != nullptr)
		p->setParameterAllocator(parameterAllocator);
	geometricActionMap[ch] = a;
}

///////////////////////////////////////////////////////////////////////////////////////////////

//void Grammar::setAction(char ch, GeometricAction * a) {
//	geometricActionMap[ch] = a;
//}

///////////////////////////////////////////////////////////////////////////////////////////////

void Grammar::setAxiom(x::vector<Symbol> const & axiom) {
	this->axiom = axiom;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Allocator<param_t>* Grammar::getParameterAllocator() const {
	return parameterAllocator;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Grammar::clear() {
	axiom.clear();
	for (auto*& p : productions) {
		delete p;
		p = nullptr;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::ostream & operator<<(std::ostream & os, Grammar::Output const & o) {
	o.symbols.write(os, ' ');
	return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Grammar::Output & Grammar::Output::operator=(Output && other) {
	delete parameterAllocator;
	//symbols.dealloc();
	symbols = std::move(other.symbols);
	geometricActionMap = other.geometricActionMap;
	return *this;
}

Grammar::Output::Output(x::vector<Symbol>&& symbols, Allocator<param_t>* parameterAllocator, GeometricAction* const* map):
	parameterAllocator(parameterAllocator),
	symbols(symbols.move()),
	geometricActionMap(map)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

Grammar::Output::~Output() {
	delete parameterAllocator;
}

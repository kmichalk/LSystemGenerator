#pragma once

#include "types.h"
#include "Production.h"
#include "Pool.h"

class Grammar
{
public:
	class Output
	{
		Allocator<param_t>* parameterAllocator;
	public:
		x::vector<Symbol> symbols;
		GeometricAction* const* geometricActionMap;
		//Output(x::vector<Symbol> const& symbols, Allocator<Symbol> const* allocator);
		Output(Output const&) = delete;
		Output(Output&&) = default;
		Output() = default;
		Output& operator=(Output const&) = delete;
		Output& operator=(Output&&);
		Output(x::vector<Symbol> && symbols, Allocator<param_t>* parameterAllocator, GeometricAction* const* map);		
		~Output();
		friend std::ostream& operator<<(std::ostream& os, Output const& o);
	};

private:
	Allocator<param_t>* oldAllocator() const;

public:
	x::vector<Symbol> axiom;
	Production* productions[256];
	mutable Allocator<param_t>* parameterAllocator;
	GeometricAction* geometricActionMap[256];

	Grammar();
	//Grammar(Grammar const& other);
	~Grammar();

	Output* produce(unsigned iterations) const;
	void setProduction(char ch, Production* p, GeometricAction* a = nullptr);
	void setAxiom(x::vector<Symbol> const& axiom);
	Allocator<param_t>* getParameterAllocator() const;
	void clear();
};


#pragma once

#include "Grammar.h"
#include "qstring.h"
#include "qfile.h"

class GrammarComputer
{
	Grammar* grammar;
	Grammar::Output* out;
	unsigned iterations;

public:
	GrammarComputer();
	~GrammarComputer();
	void setGrammar(Grammar* g);
	void setIterations(unsigned i);
	void outputToFile(QString const& filename) const;
	Grammar::Output const* compute();
	bool hasOutput() const;
	Grammar::Output const* output() const;
	Grammar const* getGrammar() const;
	unsigned getIterations() const;
};


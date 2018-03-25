#pragma once

#include "ProductionParser.h"
#include "qvector.h"
#include "qstring.h"
#include "Grammar.h"
#include "Pool.h"

class GrammarParser
{
	static QRegExp axiomRegex;
	//static QRegExp axiomLineRegex;
	static QRegExp substitutionLineRegex;

	ProductionParser* productionParser;
	mutable Grammar* grammar;

	void parseAxiom(QString const& line, Allocator<param_t>* parameterAllocator) const;
	void parseSubstitutions(QStringList& lines) const;
	void parseProductions(QStringList& lines) const;

public:
	GrammarParser(ProductionParser* productionParser);
	virtual ~GrammarParser();

	Grammar* parse(QString const& input) const;
};


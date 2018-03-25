#pragma once

#include "ExpressionParser.h"
#include "GeometricActionMap.h"
#include "Production.h"
#include "qregexp.h"

class ProductionParser
{
	static QRegExp prodLineRegex;
	static QRegExp predArgRegex;
	static QRegExp succSymbolRegex;
	static QRegExp succSymbolExprRegex;
	
	ExpressionParser<param_t>* expressionParser;
	GeometricActionMap const* geometricActionMap;

	void parsePredecessorArguments(QString const& predArgs, size_t(&argMap)[256]) const;
	void parseSymbolExpressions(QString const& successor, size_t(&argMap)[256], x::vector<Production::SymbolExpression>& symbolExprBuffer) const;
	void parseExpressions(QString const& exprSetStr, size_t(&argMap)[256], x::vector<Expression<param_t>*>& exprBuffer) const;
	GeometricAction* parseGeometricAction(QString const& str) const;

public:
	struct Output
	{
		char symbol;
		Production* production;
		GeometricAction* action = nullptr;

		__inline operator bool() const {
			return production != nullptr;
		}
	};

	ProductionParser(ExpressionParser<param_t>* expressionParser, GeometricActionMap const* geometricActionMap);
	~ProductionParser();

	virtual Output parse(QString const& line) const;
};

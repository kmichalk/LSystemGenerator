#include "ProductionParser.h"
#include "GeometricActionSequence.h"
#include <exception>
#include <iostream>

void ProductionParser::parsePredecessorArguments(QString const & predArgs, size_t(&argMap)[256]) const {
	int pos = 0;
	size_t argNum = 0;
	while ((pos = predArgRegex.indexIn(predArgs, pos)) != -1) {
		char arg = predArgRegex.cap(1)[0].toLatin1();
		argMap[arg] = argNum;
		++argNum;
		pos += predArgRegex.matchedLength();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void ProductionParser::parseSymbolExpressions(QString const & successor, size_t(&argMap)[256], x::vector<Production::SymbolExpression>& symbolExprBuffer) const {
	int pos = 0;
	while ((pos = succSymbolRegex.indexIn(successor, pos)) != -1) {
		x::vector<Expression<param_t>*> expressions;
		char symbol = succSymbolRegex.cap(1)[0].toLatin1();
		QString exprSetStr = succSymbolRegex.cap(2);

		if (!exprSetStr.isEmpty())
			parseExpressions(exprSetStr, argMap, expressions);
		
		if (expressions.empty())
			symbolExprBuffer.push_back({symbol});
		else
			symbolExprBuffer.push_back({symbol, expressions.move()});

		pos += succSymbolRegex.matchedLength();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void ProductionParser::parseExpressions(QString const & exprSetStr, size_t(&argMap)[256], x::vector<Expression<param_t>*>& exprBuffer) const {
	int posexpr = 0;
	while ((posexpr = succSymbolExprRegex.indexIn(exprSetStr, posexpr)) != -1) {
		Expression<param_t>* expr = nullptr;
		QString exprStr = succSymbolExprRegex.cap(1);
		if (!exprStr.isEmpty())
			expr = expressionParser->parse(exprStr.toStdString().data(), '}', argMap);
		exprBuffer.push_back(expr);
		posexpr += succSymbolExprRegex.matchedLength();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

GeometricAction * ProductionParser::parseGeometricAction(QString const & str) const {
	auto actionNames = str.split(QRegExp("\\s*,\\s*"), QString::SplitBehavior::SkipEmptyParts);
	x::vector<GeometricAction*> actions;
	for (auto const& name : actionNames)
		if (auto* a = geometricActionMap->get(name))
			actions.push_back(a);
	if (actions.size() > 1)
		return new GeometricActionSequence(actions.move());
	else if (actions.size() == 1)
		return actions[0];
	else
		return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////

//ProductionParser::ProductionParser(ExpressionParser<param_t>* expressionParser):
//	expressionParser(expressionParser)
//{
//}

///////////////////////////////////////////////////////////////////////////////////////////////

ProductionParser::ProductionParser(ExpressionParser<param_t>* expressionParser,GeometricActionMap const* geometricActionMap):
	expressionParser(expressionParser),
	geometricActionMap(geometricActionMap) 
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

ProductionParser::~ProductionParser() {
	delete expressionParser;
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, QString const& s) {
	return os<<s.toStdString();
}

ProductionParser::Output ProductionParser::parse(QString const& line_) const {
	QString line{line_.data()};
	if (!prodLineRegex.exactMatch(line))
		return {0, nullptr};
	char predSymbol = prodLineRegex.cap(1)[0].toLatin1();
	QString predArgs = prodLineRegex.cap(2);
	QString geomActionName = prodLineRegex.cap(3);
	QString successor = prodLineRegex.cap(4);

	//std::cout<<predSymbol<<"==="<<predArgs<<"==="<<geomActionName<<"==="<<successor<<"\n";

	size_t argMap[256]{0};
	parsePredecessorArguments(predArgs, argMap);	
	GeometricAction* action = parseGeometricAction(geomActionName);

	if (successor.isEmpty()) {
		return {predSymbol, nullptr, action};
	}
	else {
		x::vector<Production::SymbolExpression> symbolExpressions;
		parseSymbolExpressions(successor, argMap, symbolExpressions);
		return {predSymbol, new Production(symbolExpressions.move()), action};
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

//const std::exception ProductionParser::unexpectedCharacterException = std::exception("Unexpected character");
//QRegExp ProductionParser::prodLineRegex = QRegExp{"(\\S)\\s*(?:\\{(.*)\\})?\\s*->(.+)"};
//! [^\\[-]*] is wrong! minus would occur in geom action args
QRegExp ProductionParser::prodLineRegex = QRegExp{"(\\S)\\s*(?:\\{([^\\[-]*)\\})?(?:\\s*\\[\\s*(\\w+)\\s*\\]\\s*)?\\s*(?:->(.+))?"};
QRegExp ProductionParser::predArgRegex = QRegExp{"([a-z])(?:\\s*;\\s*)?"};
QRegExp ProductionParser::succSymbolRegex = QRegExp{"(\\S)\\s*(?:\\{([^}]*)\\})?\\s*"};
QRegExp ProductionParser::succSymbolExprRegex = QRegExp{"\\s*([^;]+)(?:\\s*;\\s*)?"};

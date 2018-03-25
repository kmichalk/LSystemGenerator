#include "GrammarParser.h"


void GrammarParser::parseAxiom(QString const & line, Allocator<param_t>* parameterAllocator) const  {
	x::vector<Symbol> symbols;
	int pos = 0;
	while ((pos = axiomRegex.indexIn(line, pos)) != -1) {
		char symbol = axiomRegex.cap(1)[0].toLatin1();
		QString argsStr = axiomRegex.cap(2);
		if (!argsStr.isEmpty()) {
			auto args = argsStr.split(';');
			if (args.isEmpty())
				symbols.push_back({symbol});
			else {
				Symbol s{symbol, (size_t)args.size(), parameterAllocator};
				size_t ai = 0;
				for (QString const& arg : args) {
					//! handle bad conversion
					s.parameters[ai] = arg.toFloat();
					++ai;
				}
				symbols.push_back(s);
			}					
		}
		else {
			symbols.push_back({symbol});
		}
		pos += axiomRegex.matchedLength();
	}
	grammar->setAxiom(symbols);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void GrammarParser::parseSubstitutions(QStringList& lines) const {
	while (substitutionLineRegex.exactMatch(lines.first())) {
		QString name = substitutionLineRegex.cap(1);
		QString substitution = substitutionLineRegex.cap(2);
		lines.pop_front();
		if (name .size() == 1)
			parseAxiom(substitution, grammar->getParameterAllocator());
		else {
			for (QString& line : lines)
				line.replace(name, substitution);
		}
	}
	for (auto l : lines)
		std::cout<<l.toStdString() << "\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////

void GrammarParser::parseProductions(QStringList & lines) const {
	x::vector<Production*> productions(lines.size());
	for (QString const& line : lines) {
		ProductionParser::Output out = productionParser->parse(line);
		grammar->setProduction(out.symbol, out.production, out.action);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

GrammarParser::GrammarParser(ProductionParser * productionParser):
	productionParser(productionParser),
	grammar(nullptr)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

GrammarParser::~GrammarParser() {
	delete productionParser;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Grammar * GrammarParser::parse(QString const & input) const {
	if (input.isEmpty())
		return nullptr;
	auto lines = input.split('\n');
	if (lines.isEmpty())
		return nullptr;

	grammar = new Grammar;
	parseSubstitutions(lines);
	parseProductions(lines);	
	return grammar;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QRegExp GrammarParser::axiomRegex = QRegExp("(\\S)\\s*(?:\\{\\s*([^}]+)\\s*\\}\\s*)?");
//QRegExp GrammarParser::axiomLineRegex = QRegExp("\\$\\s*=\\s*(.+)");
QRegExp GrammarParser::substitutionLineRegex = QRegExp("(\\$\\w*)\\s*=\\s*(\\S.*)");

//
//Grammar * GrammarParser::parse(QString const & input) const {
//	
//}
//
//
//Grammar * GrammarParser::parse(std::string const & input) const  {
//	return parse(QString{input.data()});
//}

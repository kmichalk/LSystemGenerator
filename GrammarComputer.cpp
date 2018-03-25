#include "GrammarComputer.h"
#include "qdatastream.h"
#include <exception>

GrammarComputer::GrammarComputer():
	grammar(nullptr),
	out(nullptr)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

GrammarComputer::~GrammarComputer() {
	delete grammar;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void GrammarComputer::setGrammar(Grammar * g) {
	delete grammar;
	grammar = g;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void GrammarComputer::setIterations(unsigned i) {
	iterations = i;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void GrammarComputer::outputToFile(QString const& filename) const {
	if (out == nullptr)
		throw std::exception("Output has not been computed.");
	QFile file(filename);
	if (!file.open(QFile::WriteOnly | QFile::Text))
		throw std::exception("Error while opening file. Output not saved.");
	QTextStream stream(&file);
	for (auto const& s : out->symbols)
		stream << s << "  ";
}

///////////////////////////////////////////////////////////////////////////////////////////////

Grammar::Output const* GrammarComputer::compute() {
	delete out;
	out = grammar->produce(iterations);
	return out;
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool GrammarComputer::hasOutput() const {
	return out != nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Grammar::Output const * GrammarComputer::output() const {
	return out;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Grammar const * GrammarComputer::getGrammar() const {
	return grammar;
}

unsigned GrammarComputer::getIterations() const {
	return iterations;
}

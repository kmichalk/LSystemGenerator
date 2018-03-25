//#include "LSystemGenerator.h"
//
//
//LSystemGenerator::LSystemGenerator():
//	geometricActionMap(new GeometricActionMap),
//	grammar(nullptr)
//{
//	geometricActionMap->setDefaults();
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//LSystemGenerator::~LSystemGenerator() {
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//void LSystemGenerator::setMap(GeometricActionMap * map) {
//	delete geometricActionMap;
//	geometricActionMap = map;
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//void LSystemGenerator::setGrammar(Grammar * grammar) {
//	delete this->grammar;
//	this->grammar = grammar;
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//TransformationSequence LSystemGenerator::generate(unsigned iterations) const {
//	//TODO optimize
//	auto outSymbols = grammar->produce(iterations).symbols;
//	return outSymbols.compute([this](auto const& s) {return GeometricActionData{geometricActionMap->get(s.ch), s.parameters}; });
//	/*x::vector<GeometricActionData> result(outSymbols.size());
//	size_t i = 0;
//	for (auto const& s : outSymbols)
//		result[i++] = {geometricActionMap->get(s.ch), s.parameters};
//	return result;*/
//}

#include "GeometricActionSequence.h"


void GeometricActionSequence::initializeName() const {
	for (auto action : sequence)
		name.append(action->getName());
}

///////////////////////////////////////////////////////////////////////////////////////////////

void GeometricActionSequence::initializeAbbreviation() const {
	abbreviation = "[";
	for (size_t i = 0, end = sequence.size() -1; i<end; ++i)
		abbreviation.append(sequence[i]->getAbbreviation()).append(',');
	abbreviation.append(sequence.back()->getAbbreviation()).append(']');
}

///////////////////////////////////////////////////////////////////////////////////////////////

GeometricActionSequence::GeometricActionSequence(x::vector<GeometricAction*>&& sequence):
	sequence(sequence)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

GeometricActionSequence::~GeometricActionSequence() {
}

///////////////////////////////////////////////////////////////////////////////////////////////

void GeometricActionSequence::apply(Painter * painter, void const * parameters) const {
	for (auto action : sequence)
		action->apply(painter, parameters);
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString GeometricActionSequence::getName() const {
	if (name.isEmpty())
		initializeName();
	return name;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString GeometricActionSequence::getAbbreviation() const {
	if (abbreviation.isEmpty())
		initializeAbbreviation();
	return abbreviation;
}

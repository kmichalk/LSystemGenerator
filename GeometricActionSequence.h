#pragma once

#include "GeometricAction.h"

class GeometricActionSequence: public GeometricAction
{
	void initializeName() const;
	void initializeAbbreviation() const;

public:
	//TODO name will change because sequence can change as user assigns actions to it
	mutable QString name;
	mutable QString abbreviation;
	x::vector<GeometricAction*> sequence;

	GeometricActionSequence(x::vector<GeometricAction*>&& sequence);
	virtual ~GeometricActionSequence();

	virtual void apply(Painter* painter, void const* parameters = nullptr) const override;
	virtual QString getName() const override;
	virtual QString getAbbreviation() const override;
};


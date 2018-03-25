#pragma once

#include "GeometricAction.h"
#include "Allocator.h"

class Transformation
{
public:
	GeometricAction* action;
	param_t* parameters;

	Transformation(GeometricAction* action);
	Transformation(GeometricAction* action, param_t* parameters, size_t paramCount, Allocator<param_t>* parameterAllocator);

	__inline void apply(Painter* painter) const {
		action->apply(painter, parameters);
	}
};

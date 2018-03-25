#include "Transformation.h"

Transformation::Transformation(GeometricAction * action):
	action(action),
	parameters(nullptr)
{
}

Transformation::Transformation(GeometricAction * action, param_t * parameters, size_t paramCount, Allocator<param_t>* parameterAllocator) :
	action(action),
	parameters(parameterAllocator->alloc(paramCount))
{
	memcpy(this->parameters, parameters, paramCount*sizeof(param_t));
}

#include "GeometricActionMap.h"
#include "GeometricActionDef.h"


GeometricActionMap::GeometricActionMap():
	data{0ull} 
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

GeometricActionMap::~GeometricActionMap() {
	for (auto* a : nameMap)
		delete a;
}

///////////////////////////////////////////////////////////////////////////////////////////////

x::vector<GeometricAction*> GeometricActionMap::map(x::vector<Symbol> const & symbols) const {
	return symbols.map(&Symbol::ch, data);
}

///////////////////////////////////////////////////////////////////////////////////////////////

#define _PUT_ACTION(_Name) { \
		auto action = new geom::_Name; \
		set(geom::_Name::ABBREVIATION, action); \
	} 

void GeometricActionMap::initialize() {
	APPLY(_PUT_ACTION, _ALL_GEOMETRIC_ACTIONS);
}

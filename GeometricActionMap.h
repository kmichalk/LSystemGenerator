#pragma once

#include "GeometricAction.h"
#include "Symbol.h"
#include "qmap.h"


class GeometricActionMap
{
	////struct GeometricActionData
	////{
	////	GeometricAction* action;
	////};

	GeometricAction* data[256];
	QMap<QString, GeometricAction*> nameMap;

public:
	GeometricActionMap();
	~GeometricActionMap();

	void set(QString const& name, GeometricAction* action);
	//GeometricAction* operator[](char ch) const;
	//GeometricAction* get(char ch) const;
	GeometricAction* get(QString const& name) const;
	x::vector<GeometricAction*> map(x::vector<Symbol> const& symbols) const;
	virtual void initialize();
};

///////////////////////////////////////////////////////////////////////////////////////////////

//__forceinline GeometricAction * GeometricActionMap::operator[](char ch) const {
//	return data[ch];
//}

///////////////////////////////////////////////////////////////////////////////////////////////

//__forceinline GeometricAction * GeometricActionMap::get(char ch) const {
//	return data[ch];
//}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline void GeometricActionMap::set(QString const& name, GeometricAction * action) {
	//data[ch] = action;
	nameMap[name] = action;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__forceinline GeometricAction * GeometricActionMap::get(QString const & name) const {
	return nameMap.value(name, nullptr);
}

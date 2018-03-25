#pragma once

#include "qvariant.h"
#include "qexception.h"
#include "Var.h"
#include "qcolor.h"

//? back to settings without QVariant
class Setting: public QVariant
{
private:
	static bool stringToBool(QString const& value, bool* ok);
	//static QColor stringToColor(QString const& str, bool* ok);

	mutable bool changed;
	QVariant::Type strictType;

	using QVariant::operator=;
	bool validateType(QMetaType::Type other) const;

public:
	//TODO: trim toString output
	const QString name;
	QString comment;

	template<class... _Arg>
	Setting(QString const& name, QVariant::Type strictType = QVariant::Invalid, _Arg const&... args);
	~Setting() = default;
	/*template<class _Arg>
	Setting& operator = (_Arg const& arg);*/
	bool operator=(QVariant const& other);
	bool operator=(QVariant && other);

	bool hasChanged() const;
	bool isUnset() const;
	QVariant::Type getStrictType() const;
	void setStrictType(QVariant::Type type);
	bool parse(QString const& str);
};

///////////////////////////////////////////////////////////////////////////////////////////////

template<class ..._Arg>
Setting::Setting(QString const & name, QVariant::Type strictType, _Arg const & ...args):
	QVariant(args...),
	changed(false),
	strictType(strictType),
	name(name) 
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

//template<class _Arg>
//__forceinline Setting & Setting::operator=(_Arg const & arg) {
//	QVariant::canConvert()
//	QVariant::operator=(arg);
//	unset = false;
//	return *this;
//}

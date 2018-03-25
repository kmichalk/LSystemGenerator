#include "Setting.h"


bool Setting::stringToBool(QString const& value, bool* ok) {
	if (value.size() != 1) {
		if (value == "true") {
			*ok = true;
			return true;
		}
		if (value == "false") {
			*ok = true;
			return false;
		}
		*ok = false;
		return false;
	}
	else {
		if (value[0] == '1') {
			*ok = true;
			return true;
		}
		if (value[0] == '0') {
			*ok = true;
			return false;
		}
		*ok = false;
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

//QColor Setting::stringToColor(QString const & str, bool* ok) {
//	return QColor()
//}

///////////////////////////////////////////////////////////////////////////////////////////////

bool Setting::validateType(QMetaType::Type other) const {
	return strictType == other || type() == QVariant::Invalid;
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool Setting::operator=(QVariant const & other) {
	if (strictType == QVariant::Invalid) {
		strictType = other.type();
		QVariant::operator=(other);
		return true;
	}
	else if (strictType == other.type()) {
		QVariant::operator=(other);
		return true;
	}
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool Setting::operator=(QVariant && other) {
	if (strictType == QVariant::Invalid) {
		strictType = other.type();
		QVariant::operator=(std::move(other));
		return true;
	}
	else if (strictType == other.type()) {
		QVariant::operator=(std::move(other));
		return true;
	}
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool Setting::hasChanged() const {
	if (changed) {
		changed = false;
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool Setting::isUnset() const {
	return type() == QVariant::Invalid;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QVariant::Type Setting::getStrictType() const {
	return strictType;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Setting::setStrictType(QVariant::Type type) {
	strictType = type;
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool Setting::parse(QString const & str) {
	bool ok = false;
	switch (strictType) {
	case QVariant::Invalid:
		return false;
	case QVariant::Bool:
	{
		bool value = stringToBool(str, &ok);
		if (ok) {
			QVariant::operator=(value);
			return true;
		}
		return true;
	}
	case QVariant::Int:
	{
		int value = str.toInt(&ok);
		if (ok) {
			QVariant::operator=(value);
			return true;
		}
		return true;
	}
	case QVariant::UInt:
	{
		unsigned value = str.toUInt(&ok);
		if (ok) {
			QVariant::operator=(value);
			return true;
		}
		return true;
	}
	case QVariant::LongLong:
	{
		long long value = str.toLongLong(&ok);
		if (ok) {
			QVariant::operator=(value);
			return true;
		}
		return true;
	}
	case QVariant::ULongLong:
	{
		unsigned long long value = str.toULongLong(&ok);
		if (ok) {
			QVariant::operator=(value);
			return true;
		}
		return true;
	}
	case QVariant::Double:
	{
		double value = str.toDouble(&ok);
		if (ok) {
			QVariant::operator=(value);
			return true;
		}
		return true;
	}
	case QVariant::Char:
	{
		if (str.size() == 1) {
			QVariant::operator=(str[0].toLatin1());
			return true;
		}
		return false;
	}
	case QVariant::String:
	{
		QVariant::operator=(str);
	}		
	case QVariant::Color:
	{
		QColor value = QColor(str);
		if (value.isValid()) {
			QVariant::operator=(value);
			return true;
		}
		return false;
	}
	default:
		break;
	}
	return false;
}


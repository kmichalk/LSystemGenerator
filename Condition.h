#pragma once


class Condition
{
public:
	virtual bool fulfilled() const abstract;
	virtual ~Condition() = default;
};



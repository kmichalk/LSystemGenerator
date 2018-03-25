#pragma once


class Job
{
public:
	Job() = default;
	virtual ~Job() = default;
	virtual void execute() abstract;
};


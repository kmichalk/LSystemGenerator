#pragma once

#include "qpoint.h"

struct Statistics
{
	float computeTime;
	float renderTime;
	float totalTime;
	unsigned axiomSymbols;
	unsigned outputSymbols;
	unsigned iterations;
	QPoint originPoint;
};

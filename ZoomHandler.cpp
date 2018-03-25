#include "ZoomHandler.h"
#include "Plot.h"
#include <cmath>



void ZoomHandler::computeParameters() {
	//c = scaleMin;
	//a = (scaleMax - c)/(sliderMax*sliderMax);
	//b = 1.0;


	/*float a1 = sliderZeroPos*sliderZeroPos;
	float b1 = sliderZeroPos;
	float r1 = 0;

	float a2 = sliderMax*sliderMax;
	float b2 = sliderMax;	
	float r2 = scaleMax;

	float t = b2/b1;
	float ta = t*a1;
	float tr = t*r1;

	a = (r2 - tr) / (a2 - ta);
	b = (r2 - a2*a)/b2;
	c = scaleMin;*/
	

	float pa1 = sliderZeroPos*sliderZeroPos;
	float pb1 = sliderZeroPos;
	float pr1 = 1;

	float pa2 = sliderMax*sliderMax;
	float pb2 = sliderMax;	
	float pr2 = scaleMax;

	float pa3 = 1;
	float pb3 = 1;
	float pr3 = scaleMin;

	float qa1 = pa1-pa3;
	float qb1 = pb1-pa3;
	float qr1 = pr1-pr3;

	float qa2 = pa2-pa3;
	float qb2 = pb2-pa3;
	float qr2 = pr2-pr3;

	float t = qb2/qb1;
	float ta = t*qa1;
	float tr = t*qr1;

	a = (qr2 - tr) / (qa2 - ta);
	b = (qr2 - qa2*a)/qb2;
	c = pr1 - pa1*a - pb1*b;
	D = b*b - 4*a*c;
	p = -b/(2*a);
	q = -D/(4*a);
	x1 = (-b - sqrt(D))/2;
	x2 = (-b + sqrt(D))/2;
}

///////////////////////////////////////////////////////////////////////////////////////////////

//ZoomHandler::ZoomHandler(int sliderMax, int sliderZeroPos, float scaleMin, float scaleMax):
//	sliderMax(sliderMax),
//	sliderZeroPos(sliderZeroPos),
//	scaleMin(scaleMin),
//	scaleMax(scaleMax)
//{
//	computeParameters();
//}

//ZoomHandler::ZoomHandler(int sliderMax, float scaleMin, float ScaleMax):
//	sliderMax(sliderMax),
//	scaleMin(scaleMin),
//	scaleMax(scaleMax)
//{
//	computeParameters();
//}

ZoomHandler::ZoomHandler(Plot * plot):
	plot(plot)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

ZoomHandler::~ZoomHandler() {
}

///////////////////////////////////////////////////////////////////////////////////////////////

float ZoomHandler::computeScale(int sliderPos) const {
	float sp = (sliderPos < 1.0f ? 1.0f : sliderPos) + p;
	return a*sp*sp + b*sp + c - q + scaleMin;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void ZoomHandler::setPlot(Plot * plot) {
	this->plot = plot;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void ZoomHandler::setParameters(int sliderMax, int sliderZeroPos, float scaleMin, float scaleMax) {
	this->sliderMax = sliderMax;
	this->sliderZeroPos = sliderZeroPos;
	this->scaleMin = scaleMin;
	this->scaleMax = scaleMax;
	computeParameters();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void ZoomHandler::processZoom(int sliderPos) const {
	float prevScale = plot->getScale();
	float scale = computeScale(sliderPos);
	plot->setScale(scale);
	QRect plotRect = plot->viewport()->rect();
	QPoint windowOffset = plot->mapFromGlobal(QCursor::pos());
	QPoint prevOrigin = plot->getOrigin() - windowOffset;
	plot->setOrigin(prevOrigin*(scale/prevScale) + windowOffset);
	plot->renderPlot();
	plot->viewport()->update();
}

#pragma once

#include "Job.h"
#include "Transformation.h"
#include "Painter.h"

class RenderJob: public Job
{
	friend class MultiThreadPlotRenderer;
	using TIter = x::vector<Transformation>::const_iterator;

	QPixmap* pixmap;
	QPen pen;
	QTransform rotation;
	QPoint origin;
	QPoint offset;
	TIter tbegin;
	TIter tend;
	//Painter painter;
	float scale;

public:
	RenderJob();
	RenderJob(QPixmap* pixmap, Painter::State const& beginState, TIter tbegin, TIter tend);
	virtual ~RenderJob();
	virtual void execute() override;
};


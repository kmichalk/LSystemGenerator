#pragma once

#include "PlotRenderer.h"
#include "ThreadPool.h"
#include "RenderJob.h"


class MultiThreadPlotRenderer: public PlotRenderer, public ThreadPool
{
	x::vector<Job*> renderJobs;

	void generateTransformations(Grammar::Output const* output);
	void processTransformations(Painter& painter, QPoint const & beginPoint, QPen const & defaultPen, float scale);

public:
	MultiThreadPlotRenderer();
	virtual ~MultiThreadPlotRenderer();
	//virtual void setThreads(size_t n) override;
	//virtual void render(Painter* painter, Grammar::Output const* output) const;
	//virtual void render(Painter* painter, Grammar::Output const* output) override;
	virtual void render(QPixmap* pixmap, Grammar::Output const* output, float scale, QPoint const& beginPoint = QPoint(0,0), QPen const& defaultPen = QPen(QColor(Qt::black)), QColor const& backgroundColor = Qt::black) override;
	virtual void render(QPixmap* pixmap, float scale = 1.0f) override;
};


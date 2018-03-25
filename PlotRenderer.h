#pragma once

#include "Grammar.h"
#include "Transformation.h"
#include "qpixmap.h"
#include "qprogressbar.h"


class PlotRenderer
{
	//mutable QPixmap* pixmap_;
	//mutable Painter* painter_;

	/*void beginRender() const;
	void endRender() const;*/
protected:
	x::vector<Transformation> transformations;
	Pool<param_t> parameterAllocator;
	Painter::State beginState;
	QProgressBar* progressBar;

	void renderWithProgressBar(Painter& painter, Grammar::Output const* output);

public:
	PlotRenderer() = default;
	//PlotRenderer(int width, int height);
	virtual ~PlotRenderer() = default;
	//void set(int width, int height);
	//void setOrigin(QPoint const& origin);
	//QPixmap const* pixmap() const;
	//QPainter* painter();
	//virtual void render(Painter* painter, Grammar::Output const* output);
	//virtual void render(QPixmap* pixmap, Grammar::Output const* output, QPoint const& beginPoint = QPoint(0,0), QPen const& defaultPen = QPen(QColor(Qt::black)), float scale = 1.0f);
	virtual void render(QPixmap* pixmap, Grammar::Output const* output, float scale, QPoint const& beginPoint = QPoint(0,0), QPen const& defaultPen = QPen(QColor(Qt::black)), QColor const& backgroundColor = Qt::black);
	//virtual void render(Painter* painter, Grammar::Output const* output, x::vector<Transformation>& transformationBuffer, Allocator<param_t>* parameterAllocator) const;
	virtual void render(QPixmap* pixmap, float scale = 1.0f);
	void assignProgressBar(QProgressBar* bar);
	void removeProgressBar();
};


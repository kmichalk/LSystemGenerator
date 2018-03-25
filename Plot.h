#pragma once

#include "qgraphicsview.h"
#include "QtOpenGL\qglpixelbuffer.h"
#include "Painter.h"
#include "GeometricActionMap.h"
#include "Grammar.h"
#include "DragHandler.h"
#include "SettingsManager.h"
#include "Transformation.h"
#include "ZoomHandler.h"
#include "SettingsUser.h"
#include "MultiThreadPlotRenderer.h"

class Plot: public QGraphicsView, public SettingsUser
{
	Q_OBJECT;

	//Painter renderPainter;
	QPainter painter;
	QPixmap* renderPixmap;
	QPoint origin;
	QPoint offset;
	QPoint renderOrigin;
	DragHandler dragHandler;
	PlotRenderer plotRenderer;
	float scale;
	//Pool<param_t> transformationParameterAllocator;
	//x::vector<Transformation> renderTransformations;

	SETTINGS(
		(int, maxXSize, 4000),
		(int, maxYSize, 4000),
		(QColor, extrasColor, QColor(100,100,100)),
		(QColor, defaultDrawColor, QColor(150, 150, 150)),
		(float, defaultPenWidth, 1.0f),
		(QColor, plotBgColor, QColor(50, 50, 50)),
		(bool, stepMode, false),
		(bool, extras, true)
	);
	
	void drawExtras();
	void drawBackground();
	void drawRenderedPixmap();
	void connectSignals();
	void flipRenderPixmap();
	void beginRender();
	void endRender();
	QPoint viewportSize() const;
	bool imageOutOfBounds() const;

public:
	Plot(QWidget* parent = Q_NULLPTR);
	~Plot();

	virtual void paintEvent(QPaintEvent* event) override;
	void renderPlot(Grammar::Output const& output);
	void renderPlot();
	void setOrigin(QPoint p);
	void resetOrigin();
	QPoint getOrigin() const;
	void setOffset(QPoint p);
	QPoint getOffset() const;
	void setScale(float value);
	float getScale() const;
	PlotRenderer* renderer();

	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void wheelEvent(QWheelEvent* event) override;

signals:
	void scrolled(int delta);
};


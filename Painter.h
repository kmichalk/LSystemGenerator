#pragma once

#include "qpainter.h"
#include "types.h"

class Painter: public QPainter
{
public:
	struct State
	{
		QTransform transform;
		QPen pen;
	};

private:
	x::vector<State> stateStack;
	mutable State state;
	float scale;
	QRect viewportRect;

	//using QPainter::begin;
	void updateState() const;

public:
	static constexpr size_t DEFAULT_STATE_STACK_SIZE = 50;
	static constexpr float DEFAULT_WIDTH = 1.0;
	static const QColor DEFAULT_COLOR;


	//using QPainter::QPainter;
	Painter();
	~Painter();

	State const& getState() const;
	void restoreState(State const& state);
	void scaledTranslate(QPoint const& p);
	void moveForward(param_t length);
	void drawLineForward(param_t length);
	void drawLineForwardAndMove(param_t length);
	void setPenWidth(param_t width);
	void setColor(param_t r, param_t g, param_t b);
	void rotateClockwise(param_t angle);
	void rotateAnticlockwise(param_t angle);
	void drawCircle(param_t r);
	void drawSquare(param_t a);
	void drawRect(param_t a, param_t b);
	void _translate(param_t x, param_t y);
	void setPosition(param_t x, param_t y);

	void pushState();
	void popState();
	void setScale(float scale);
	float getScale() const;
	//bool begin(QPaintDevice* paintDevice);
};


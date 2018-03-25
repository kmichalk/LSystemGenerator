#pragma once

#include "qpoint.h"
#include "qcursor.h"
#include "qevent.h"

class Plot;

class DragHandler: public QObject
{
	Q_OBJECT;

	Plot* parent;
	QPoint grabOffset;
	QPoint grabMousePos;
	Qt::CursorShape prevShape;
	bool dragging;

public:
	DragHandler(Plot* parent);
	//DragHandler();
	~DragHandler();

	bool isDragging() const;
	QPoint getOffset() const;
	void grab();
	void release();
};

///////////////////////////////////////////////////////////////////////////////////////////////

__inline bool DragHandler::isDragging() const {
	return dragging;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__inline QPoint DragHandler::getOffset() const {
	return grabOffset + QCursor::pos() - grabMousePos;
}
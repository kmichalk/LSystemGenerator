#include "Plot.h"
#include <iostream>


void Plot::drawExtras() {
	painter.setPen(QPen(QBrush(extrasColor), 1.0));
	painter.drawLine(0, origin.y(), width(), origin.y());
	painter.drawLine(origin.x(), 0, origin.x(), height());
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::drawBackground() {
	painter.fillRect(rect(), plotBgColor);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::drawRenderedPixmap() {
	painter.drawPixmap(origin-renderOrigin, *renderPixmap);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::connectSignals() {
}

///////////////////////////////////////////////////////////////////////////////////////////////

Plot::Plot(QWidget * parent):
	QGraphicsView(parent),
	painter(),
	//renderPainter(),
	renderPixmap(nullptr),
	origin(0, 0),
	offset(0, 0),
	renderOrigin(0, 0),
	dragHandler(this),
	plotRenderer(),
	scale(1.0f)
	//transformationParameterAllocator(),
	//renderTransformations(0x100) 
{
	//plotRenderer.setThreads(5);
	//plotRenderer.run();
}

///////////////////////////////////////////////////////////////////////////////////////////////

Plot::~Plot() {
	delete renderPixmap;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::paintEvent(QPaintEvent * event) {
	if (renderPixmap == nullptr)
		return;
	painter.begin(viewport());
	drawBackground();
	if (extras)
		drawExtras();
	drawRenderedPixmap();
	painter.end();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::renderPlot(Grammar::Output const & output) {
	if (stepMode) {
		//beginRender();
		//renderTransformations.erase();
		//transformationParameterAllocator.clear();
		//for (auto const& s : output.symbols)
		//	if (GeometricAction* action = output.geometricActionMap[s.ch]) {
		//		action->apply(&renderPainter, s.parameters);
		//		Painter::State state = renderPainter.getState();
		//		renderPainter.end();
		//		renderTransformations.push_back({action, s.parameters, s.paramCount, &transformationParameterAllocator});
		//		viewport()->repaint();
		//		viewport()->update();
		//		repaint();
		//		update();
		//		std::cout<<s.ch;
		//		std::cin.get();
		//		//Sleep(500);
		//		renderPainter.begin(renderPixmap);
		//		renderPainter.restoreState(state);
		//	}
		//endRender();
	}
	else {
		beginRender();
		plotRenderer.render(renderPixmap, &output, scale, renderOrigin, 
							QPen(QBrush(defaultDrawColor), defaultPenWidth));
		//renderTransformations.clear();
		//transformationParameterAllocator.clear();
		//for (auto const& s : output.symbols) {
		//	//std::cout << s.ch<<std::endl;
		//	if (GeometricAction* action = output.geometricActionMap[s.ch]) {
		//		action->apply(&renderPainter, s.parameters);
		//		renderTransformations.push_back({action, s.parameters, s.paramCount, &transformationParameterAllocator});
		//	}
		//}
		endRender();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::renderPlot() {
	beginRender();
	plotRenderer.render(renderPixmap, scale);
	/*for (auto t : renderTransformations)
		t.apply(&renderPainter);*/
	endRender();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::flipRenderPixmap() {
	QTransform flip;
	flip.scale(1, -1);
	*renderPixmap = renderPixmap->transformed(flip);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::beginRender() {
	delete renderPixmap;
	int sizeX = maxXSize;
	int sizeY = maxYSize;
	renderOrigin = {sizeX/2, sizeY/2};
	renderPixmap = new QPixmap(sizeX, sizeY);
	renderPixmap->fill(QColor{255,255,255,0});
	//renderPainter.setPen(QPen(QBrush(defaultDrawColor), defaultPenWidth));
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::endRender() {
	//renderPainter.end();
	flipRenderPixmap();
}

///////////////////////////////////////////////////////////////////////////////////////////////

QPoint Plot::viewportSize() const {
	QRect viewportRect = viewport()->rect();
	return {viewportRect.width(), viewportRect.height()};
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool Plot::imageOutOfBounds() const {
	return !renderPixmap->rect().translated(origin-renderOrigin).contains(viewport()->rect(), true);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::setScale(float value) {
	scale = value;
	//renderPainter.setScale(value);
}

///////////////////////////////////////////////////////////////////////////////////////////////

float Plot::getScale() const {
	return scale;
	//return renderPainter.getScale();
}

///////////////////////////////////////////////////////////////////////////////////////////////

PlotRenderer * Plot::renderer() {
	return &plotRenderer;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::setOrigin(QPoint p) {
	origin = p;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::resetOrigin() {
	origin = {width()/2, height()/2};
}

///////////////////////////////////////////////////////////////////////////////////////////////

QPoint Plot::getOrigin() const {
	return origin;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::setOffset(QPoint p) {
	offset = p;
}

///////////////////////////////////////////////////////////////////////////////////////////////

QPoint Plot::getOffset() const {
	return offset;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::mouseMoveEvent(QMouseEvent * event) {
	if (dragHandler.isDragging()) {
		origin = dragHandler.getOffset();
		viewport()->update();
	}
	//std::cout<<"move\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::mousePressEvent(QMouseEvent * event) {
	dragHandler.grab();
	setCursor(Qt::CursorShape::ClosedHandCursor);
	//std::cout<<"grab\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::mouseReleaseEvent(QMouseEvent * event) {
	dragHandler.release();
	setCursor(Qt::CursorShape::ArrowCursor);
	//std::cout<<"release\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////

void Plot::wheelEvent(QWheelEvent * event) {
	emit scrolled(event->delta());
}

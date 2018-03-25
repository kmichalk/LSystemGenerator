#include "PlotRenderer.h"

//void PlotRenderer::beginRender() const {
//}
//
//void PlotRenderer::endRender() const {
//}

//PlotRenderer::PlotRenderer()
//	//pixmap_(nullptr)
//{
//}

//PlotRenderer::PlotRenderer(int width, int height):
//	pixmap_(new QPixmap(width, height))
//{
//}

//PlotRenderer::~PlotRenderer() {
//	//delete pixmap_;
//	//delete painter_;
//}

//void PlotRenderer::set(int width, int height) {
//	delete pixmap_;
//	pixmap_ = new QPixmap(width, height);
//}

//void PlotRenderer::setOrigin(QPoint const & origin) {
//	
//}

//QPixmap const* PlotRenderer::pixmap() const {
//	return pixmap_;
//}

//QPainter * PlotRenderer::painter() {
//	return painter_;
//}

//void PlotRenderer::render(Painter* painter,  Grammar::Output const * output) {
//	transformations.clear();
//	parameterAllocator.clear();
//	beginState = painter->getState();
//	for (auto const& s : output->symbols) {
//		if (GeometricAction* action = output->geometricActionMap[s.ch]) {
//			action->apply(painter, s.parameters);
//			transformations.push_back({action, s.parameters, s.paramCount, &parameterAllocator});
//		}
//	}
//	/*for (auto const& s : output->symbols) {
//		if (GeometricAction* action = output->geometricActionMap[s.ch]) 
//			action->apply(painter, s.parameters);
//	}*/
//}

void PlotRenderer::renderWithProgressBar(Painter& painter, Grammar::Output const* output) {
	size_t i = 0;
	size_t percentSize = output->symbols.size()/100;
	for (auto const& s : output->symbols) {
		if (GeometricAction* action = output->geometricActionMap[s.ch]) {
			action->apply(&painter, s.parameters);
			transformations.push_back({action, s.parameters, s.paramCount, &parameterAllocator});
		}
		if (++i >= percentSize)
			progressBar->setValue(progressBar->value() + 1);
	}
}

//void PlotRenderer::render(QPixmap * pixmap, Grammar::Output const * output, QPoint const & beginPoint, QPen const & defaultPen, float scale) {
//	render(pixmap, output, beginPoint, defaultPen, Qt::black, scale);
//}

///////////////////////////////////////////////////////////////////////////////////////////////

//void PlotRenderer::render(Painter * painter, 
//						  Grammar::Output const * output, 
//						  x::vector<Transformation>& transformationBuffer, 
//						  Allocator<param_t>* parameterAllocator) const {
//	transformationBuffer.clear();
//	parameterAllocator->clear();
//	for (auto const& s : output->symbols) {
//		if (GeometricAction* action = output->geometricActionMap[s.ch]) {
//			action->apply(painter, s.parameters);
//			transformationBuffer.push_back({action, s.parameters, s.paramCount, parameterAllocator});
//		}
//	}
//}

///////////////////////////////////////////////////////////////////////////////////////////////

void PlotRenderer::render(QPixmap * pixmap, Grammar::Output const * output, float scale, QPoint const & beginPoint, QPen const & defaultPen, QColor const & backgroundColor) {
	Painter painter;
	painter.setScale(scale);
	painter.begin(pixmap);
	painter.translate(beginPoint);
	painter.setPen(defaultPen);
	transformations.clear();
	parameterAllocator.clear();
	beginState = painter.getState();
	if (backgroundColor != QColor(Qt::black))
		pixmap->fill(backgroundColor);
	if (progressBar != nullptr)
		renderWithProgressBar(painter, output);
	else
		for (auto const& s : output->symbols) {
			if (GeometricAction* action = output->geometricActionMap[s.ch]) {
				action->apply(&painter, s.parameters);
				transformations.push_back({action, s.parameters, s.paramCount, &parameterAllocator});
			}
		}
	painter.end();
}

void PlotRenderer::render(QPixmap* pixmap, float scale) {
	Painter painter;
	painter.setScale(scale);
	painter.begin(pixmap);
	painter.restoreState(beginState);
	for (auto const& t : transformations)
		t.apply(&painter);
	painter.end();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void PlotRenderer::assignProgressBar(QProgressBar * bar) {
	progressBar = bar;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void PlotRenderer::removeProgressBar() {
	progressBar = nullptr;
}


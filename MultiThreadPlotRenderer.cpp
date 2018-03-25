#include "MultiThreadPlotRenderer.h"



void MultiThreadPlotRenderer::generateTransformations(Grammar::Output const * output) {
	transformations.clear();
	parameterAllocator.clear();
	for (auto const& s : output->symbols) {
		if (GeometricAction* action = output->geometricActionMap[s.ch])
			transformations.push_back({action, s.parameters, s.paramCount, &parameterAllocator});
	}
}

void MultiThreadPlotRenderer::processTransformations(Painter & painter, QPoint const & beginPoint, QPen const & defaultPen, float scale) {
	float scaleRev = 1.0f/scale;
	auto tbegin = transformations.cbegin();
	size_t nThreads = threadsNumber();
	size_t nTrans = transformations.size();
	size_t jobNTrans = nTrans / nThreads;
	for (size_t thi = 0; thi < nThreads; ++thi) {
		RenderJob* job = new RenderJob;
		renderJobs.push_back(job);
		auto tend = tbegin + jobNTrans;
		if (tend > transformations.end())
			tend = transformations.end();
		Painter::State const& state = painter.getState();
		job->origin = beginPoint;
		job->rotation = state.transform;
		job->rotation.translate(-state.transform.dx(), -state.transform.dy());
		job->offset = QPoint(state.transform.dx(), state.transform.dy())/scale;
		job->pen = state.pen;
		job->tbegin = tbegin;
		job->tend = tend;
		for (; tbegin < tend; ++tbegin)
			tbegin->apply(&painter);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

MultiThreadPlotRenderer::MultiThreadPlotRenderer():
	renderJobs(10)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

MultiThreadPlotRenderer::~MultiThreadPlotRenderer() {
	renderJobs.delete_each();
}

///////////////////////////////////////////////////////////////////////////////////////////////

//void MultiThreadPlotRenderer::setThreads(size_t n) {
//	ThreadPool::setThreads(n);
//	renderJobs.delete_each().clear();
//	repeat(n)
//		renderJobs.push_back(new RenderJob);
//}

///////////////////////////////////////////////////////////////////////////////////////////////

//void MultiThreadPlotRenderer::render(Painter * painter, Grammar::Output const * output) {
//	generateTransformations(output);
//	auto tbegin = transformations.cbegin();
//	size_t nThreads = threadsNumber();
//	size_t nTrans = transformations.size();
//	size_t jobNTrans = nTrans / nThreads;
//	renderJobs.delete_each().clear();
//	for (size_t thi = 0; thi < nThreads; ++thi) {
//		RenderJob* job = new RenderJob;
//		renderJobs.push_back(job);
//		auto tend = tbegin + jobNTrans;
//		if (tend > transformations.end())
//			tend = transformations.end();
//		job->beginState = painter->getState();
//		job->tbegin = tbegin;
//		job->tend = tend;
//		for (; tbegin < tend; ++tbegin)
//			tbegin->apply(painter);
//	}
//}

///////////////////////////////////////////////////////////////////////////////////////////////

void MultiThreadPlotRenderer::render(QPixmap * pixmap, Grammar::Output const * output, float scale, QPoint const & beginPoint, QPen const & defaultPen, QColor const& backgroundColor) {
	generateTransformations(output);
	renderJobs.delete_each().clear();
	Painter painter;
	painter.setScale(scale);
	painter.begin(pixmap);
	painter.translate(beginPoint);
	painter.setPen(defaultPen);
	processTransformations(painter, beginPoint, defaultPen, scale);
	painter.end();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void MultiThreadPlotRenderer::render(QPixmap * pixmap, float scale) {
	for (auto job : renderJobs) {
		RenderJob* rjob = static_cast<RenderJob*>(job);
		rjob->pixmap = pixmap;
		rjob->scale = scale;
	}
	setJobs(renderJobs);
	finish();
}

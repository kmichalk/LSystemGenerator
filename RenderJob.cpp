#include "RenderJob.h"



RenderJob::RenderJob():
	pixmap(nullptr),
	pen(),
	//beginState(),
	origin(0,0),
	offset(0,0),
	tbegin(*(x::vector<Transformation> const*)nullptr, 0),
	tend(*(x::vector<Transformation> const*)nullptr, 0),
	//painter(),
	scale(1.0f)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

RenderJob::RenderJob(QPixmap* pixmap, Painter::State const & beginState, TIter tbegin, TIter tend):
	pixmap(pixmap),
	//beginState(beginState),
	tbegin(tbegin),
	tend(tend),
	//painter(),
	scale(1.0f)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

RenderJob::~RenderJob() {
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RenderJob::execute() {
	Painter painter;
	if (!painter.begin(pixmap)) {
		std::cout<<"inactive\n";
		//_sleep(100);
		return;
	}
	while (!painter.isActive()) {
		//painter.end();
		std::cout<<"inactive\n";
		//_sleep(100);
		return;
	}
	painter.setScale(scale);
	painter.setPen(pen);
	painter.setTransform(rotation);
	painter.translate(origin + offset*scale);
	for (auto t = tbegin; t !=tend; ++t)
		t->apply(&painter);
	painter.end();
}

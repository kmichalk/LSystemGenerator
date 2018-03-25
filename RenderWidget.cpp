#include "RenderWidget.h"


void RenderWidget::connectSignals() {
	//std::cout<<__FUNCSIG__<<"\n";
	/*connect(ui.renderButton, SIGNAL(clicked()),
			this, SLOT(on_renderButton_clicked()));*/
	connect(ui.autoCropCheckBox, SIGNAL(checked(bool)),
			this, SLOT(on_autoCropCheckBox_checked(bool)));
}

///////////////////////////////////////////////////////////////////////////////////////////////

QPixmap RenderWidget::crop(QPixmap const & pixmap) const {
	auto img = pixmap.toImage();
	auto size = img.size();
	int w = size.width();
	int h = size.height();
	int minX = 0;
	int maxX = w;
	int minY = 0;
	int maxY = h;
	for (int x = 0; x<w; ++x) {
		for (int y = 0; y<h; ++y) {
			auto p = img.pixel(x, y);
			if ((p & 0x00FFFFFF) != (renderBackgroundColor.value().rgb() & 0x00FFFFFF)) {
				minX = x;
				goto _MAX_X_;
			}
		}
	}
	_MAX_X_:
	for (int x=w-1; x>=0; --x) {
		for (int y = 0; y<h; ++y) {
			auto p = img.pixel(x, y);
			if ((p & 0x00FFFFFF) != (renderBackgroundColor.value().rgb() & 0x00FFFFFF)) {
				maxX = x;
				goto _MIN_Y_;
			}
		}
	}
	_MIN_Y_:
	for (int y = 0; y<h; ++y) {
		for (int x = 0; x<w; ++x) {
			auto p = img.pixel(x, y);
			if ((p & 0x00FFFFFF) != (renderBackgroundColor.value().rgb() & 0x00FFFFFF)) {
				minY = y;
				goto _MAX_Y_;
			}
		}
	}
	_MAX_Y_:
	for (int y=h-1; y>=0; --y) {
		for (int x = 0; x<w; ++x) {
			auto p = img.pixel(x, y);
			if ((p & 0x00FFFFFF) != (renderBackgroundColor.value().rgb() & 0x00FFFFFF)) {
				maxY = y;
				goto _END_;
			}
		}
	}
	_END_:
	return pixmap.copy(minX, minY, maxX-minX+1, maxY-minY+1);
}

///////////////////////////////////////////////////////////////////////////////////////////////

RenderWidget::RenderWidget(QWidget* parent):
	QWidget(parent),
	renderer(nullptr),
	grammarComputer(new GrammarComputer),
	grammarEditor(nullptr),
	parser(nullptr)
{
	ui.setupUi(this);
	connectSignals();
}

///////////////////////////////////////////////////////////////////////////////////////////////

RenderWidget::~RenderWidget() {
	delete grammarComputer;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RenderWidget::setRenderDirectory(QString dir) {
	renderDirectory = dir;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RenderWidget::setRenderer(PlotRenderer * renderer) {
	this->renderer = renderer;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RenderWidget::setGrammarEditor(QTextEdit * editor) {
	grammarEditor = editor;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RenderWidget::setGrammarParser(GrammarParser * parser) {
	this->parser = parser;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RenderWidget::setGrammar(Grammar * grammar) {
	delete grammarComputer;
	grammarComputer = new GrammarComputer;
	grammarComputer->setGrammar(grammar);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RenderWidget::on_autoCropCheckBox_stateChanged(int state) {
	autoCrop = bool(state);
}

///////////////////////////////////////////////////////////////////////////////////////////////

//void RenderWidget::setGrammarComputer(GrammarComputer * grammarComputer) {
//	this->grammarComputer = grammarComputer;
//}

///////////////////////////////////////////////////////////////////////////////////////////////

void RenderWidget::on_renderButton_clicked() {
	std::cout<<__FUNCSIG__<<"\n";
	bool ok = true;
	unsigned offsetX = ui.offsetXTextBox->toPlainText().toInt(&ok);
	unsigned offsetY = ui.offsetYTextBox->toPlainText().toInt(&ok);
	unsigned fileSizeX = ui.fileSizeXTextBox->toPlainText().toInt(&ok);
	unsigned fileSizeY = ui.fileSizeYTextBox->toPlainText().toInt(&ok);
	unsigned iterations = ui.iterationsTextBox->toPlainText().toInt(&ok);
	float scale = ui.scaleTextBox->toPlainText().toFloat(&ok);
	QColor defaultColor = QColor(ui.defaultColorTextBox->toPlainText());
	QColor backgroundColor = QColor(ui.iterationsTextBox->toPlainText());
	QString fileName = ui.fileNameTextBox->toPlainText();

	if (!ok) return;

	grammarComputer->setGrammar(parser->parse(grammarEditor->toPlainText()));
	grammarComputer->setIterations(iterations);
	Grammar::Output const* output = grammarComputer->compute();

	QPixmap pixmap(fileSizeX, fileSizeY);
	ui.renderProgressBar->setValue(0);
	renderer->assignProgressBar(ui.renderProgressBar);
	renderer->render(&pixmap, output, scale, QPoint(offsetX, offsetY), QPen(QBrush(defaultColor), 1), backgroundColor);
	renderer->removeProgressBar();
	QTransform flip;
	flip.scale(1, -1);
	pixmap = pixmap.transformed(flip);
	if (autoCrop)
		pixmap = crop(pixmap);	
	pixmap.save(renderDirectory + (renderDirectory.endsWith('\\') ? "" : "\\") + fileName);
}
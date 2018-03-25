#include "LSystemProject.h"
#include "ExpressionFactory.h"
#include "NPNExpressionParser.h"
#include "qfiledialog.h"
#include "qtextstream.h"
#include <thread>
#include <iostream>
#include <sstream>
#include <iomanip>

LSystemProject::LSystemProject(QWidget *parent): 
	QMainWindow(parent),
	geometricActionMap(),
	grammarParser(new ProductionParser(new NPNExpressionParser<param_t>, &geometricActionMap)),
	globalSettings(),
	zoomHandler(),
	settingseEditor(),
	renderWidget()
{
	ui.setupUi(this);
	ui.plot->resetOrigin();
	connectSignals();
	geometricActionMap.initialize();
	//setDefaultSettings();
	initializeSettings(globalSettings);
	Plot::initializeSettings(globalSettings);
	RenderWidget::initializeSettings(globalSettings);
	zoomHandler.setPlot(ui.plot);
	zoomHandler.setParameters(99, 20, 0.1, 50);
	settingseEditor.setSettingsManager(&globalSettings);

	globalSettings.insert("test", QColor(150, 150, 150));
	QColor c = globalSettings.get("test").value<QColor>();
	for (auto* settingsUser : SettingsUser::instances())
		settingsUser->loadSettings(globalSettings);
}

LSystemProject::~LSystemProject() {
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::paintEvent(QPaintEvent * event) {
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::on_openFileButton_clicked() {
	std::cout<<"click\n";
	QString filename = QFileDialog::getOpenFileName(this,
													tr("Open grammar file"), 
													openDirectory,
													tr("Text files (*.txt);;All files (*)"));
	QFile file(filename);
	if (!file.open(QFile::ReadOnly | QFile::Text))
		return; //TODO error
	ui.grammarEditor->setText(QTextStream{&file}.readAll());
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::on_saveFileButton_clicked() {
	QString filename = QFileDialog::getSaveFileName(this,
													tr("Save grammar file"), 
													saveDirectory,
													tr("Text files (*.txt);;All files (*)"));
	QFile file(filename);
	if (!file.open(QFile::WriteOnly | QFile::Text))
		return; //TODO error
	file.write(ui.grammarEditor->toPlainText().toStdString().data());
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::on_outputButton_clicked() {
	if (!grammarComputer.hasOutput())
		return;
	QString filename = QFileDialog::getSaveFileName(this,
													tr("Save production output"), 
													saveDirectory,
													tr("Text files (*.txt);;All files (*)"));
	grammarComputer.outputToFile(filename);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::on_settingsButton_clicked() {
	std::cout<<"settings\n";
	settingseEditor.show();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::on_zoomSlider_sliderMoved(int pos) {
	zoomHandler.processZoom(pos);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::on_plot_scrolled(int delta) {
	//float scrollSensibility = globalSettings.get("scrollSensibility").toFloat();
	float scrollSensibility = 0.02f;
	int sliderPos = x::cutr(ui.zoomSlider->sliderPosition() + scrollSensibility*delta, 
							ui.zoomSlider->minimum(),
							ui.zoomSlider->maximum());
	ui.zoomSlider->setSliderPosition(sliderPos);
	on_zoomSlider_sliderMoved(sliderPos);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::on_stepModeCheckBox_stateChanged(int state) {
	auto& s = globalSettings.get("stepMode");
	if (state == Qt::CheckState::Checked)
		s = true;
	else if (state == Qt::CheckState::Unchecked)
		s = false;
}

void LSystemProject::on_extrasCheckBox_stateChanged(int state) {
	auto& s = globalSettings.get("extras");	
	if (state == Qt::CheckState::Checked)
		s = true;
	else if (state == Qt::CheckState::Unchecked)
		s = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::on_renderButton_clicked() {
	renderWidget.setGrammarParser(&grammarParser);
	renderWidget.setGrammarEditor(ui.grammarEditor);
	renderWidget.setRenderDirectory(renderDirectory);
	renderWidget.setRenderer(ui.plot->renderer());
	renderWidget.show();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::on_computeButton_clicked() {	
	unsigned iterations = ui.iterationsTextBox->toPlainText().toInt();
	statistics.iterations = iterations;
	grammarComputer.setIterations(iterations);
	QPoint origin{ui.offsetXTextBox->toPlainText().toInt(), ui.offsetYTextBox->toPlainText().toInt()};
	//ui.plot->setOffset(origin);
	statistics.originPoint = origin;
	grammarComputer.setGrammar(grammarParser.parse(ui.grammarEditor->toPlainText()));
	compute();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::compute() {
	computeTimer.tic();
	auto out = grammarComputer.compute();
	statistics.computeTime = computeTimer.toc();
	statistics.axiomSymbols = grammarComputer.getGrammar()->axiom.size();
	statistics.outputSymbols = out->symbols.size();
	//std::cout<<"symbols: "<<out->symbols.size();
	renderTimer.tic();
	ui.plot->renderPlot(*out);
	statistics.renderTime = renderTimer.toc();
	statistics.totalTime = statistics.renderTime + statistics.computeTime;
	ui.plot->viewport()->update();
	generateStatisticsInfo();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void LSystemProject::connectSignals() {
	disconnect(ui.computeButton, 0, 0, 0);
	disconnect(ui.openFileButton, 0, 0, 0);
	disconnect(ui.saveFileButton, 0, 0, 0);
	disconnect(ui.outputButton, 0, 0, 0);
	disconnect(ui.zoomSlider, 0, 0, 0);
	disconnect(ui.settingsButton, 0, 0, 0);
	disconnect(ui.plot, 0, 0, 0);
	disconnect(ui.stepModeCheckBox, 0, 0, 0);
	disconnect(ui.extrasCheckBox, 0, 0, 0);
	connect(ui.computeButton, SIGNAL(clicked()),
			this, SLOT(on_computeButton_clicked()));
	connect(ui.openFileButton, SIGNAL(clicked()),
			this, SLOT(on_openFileButton_clicked()));
	connect(ui.saveFileButton, SIGNAL(clicked()),
			this, SLOT(on_saveFileButton_clicked()));
	connect(ui.outputButton, SIGNAL(clicked()),
			this, SLOT(on_outputButton_clicked()));
	connect(ui.zoomSlider, SIGNAL(sliderMoved(int)),
			this, SLOT(on_zoomSlider_sliderMoved(int)));
	connect(ui.settingsButton, SIGNAL(clicked()),
			this, SLOT(on_settingsButton_clicked()));
	connect(ui.plot, SIGNAL(scrolled(int)),
			this, SLOT(on_plot_scrolled(int)));
	connect(ui.stepModeCheckBox, SIGNAL(stateChanged(int)),
			this, SLOT(on_stepModeCheckBox_stateChanged(int)));
	connect(ui.extrasCheckBox, SIGNAL(stateChanged(int)),
			this, SLOT(on_extrasCheckBox_stateChanged(int)));
}

void LSystemProject::generateStatisticsInfo() {
	std::stringstream out;
	out.precision(5);
	out << std::fixed;
	out << std::left;
	out << std::setw(20) << "compute time:" << statistics.computeTime << "\n";
	out << std::setw(20) << "render time:" << statistics.renderTime << "\n";
	out << std::setw(20) << "total time:" << statistics.totalTime << "\n";
	out << std::setw(20) << "axiom symbols:" << statistics.axiomSymbols << "\n";
	out << std::setw(20) << "output symbols:" << statistics.outputSymbols << "\n";
	out << std::setw(20) << "iterations:" << statistics.iterations;
	//out << std::setw(20) << "origin point:" << "(" << statistics.originPoint.x() << ", " << statistics.originPoint.y() << ")";
	ui.statisticsBrowser->setText(QString(out.str().data()));
}

///////////////////////////////////////////////////////////////////////////////////////////////

//void LSystemProject::setDefaultSettings() {
//	globalSettings.insert<QString>("saveDirectory", "C:\\Users\\user\\Desktop\\lsystem");
//	globalSettings.insert<QString>("openDirectory", "C:\\Users\\user\\Desktop\\lsystem");
//}

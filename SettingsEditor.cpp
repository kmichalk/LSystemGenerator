#include "SettingsEditor.h"
#include "SettingsTableModel.h"
#include "qheaderview.h"


void SettingsEditor::initializeGeometry() {
	int rowHeight = model->rowHeight();
	int nameColumnWidth = model->nameColumnWidth();
	int valueColumnWidth = model->valueColumnWidth();
	int rowCount = model->rowCount();
	for (int i = 0; i < rowCount; ++i)
		setRowHeight(i, rowHeight);
	setColumnWidth(model->nameColumnNumber(), nameColumnWidth);
	setColumnWidth(model->valueColumnNumber(), valueColumnWidth);
	QPoint position =
		parent() != nullptr ?
		parentWidget()->pos() + QPoint{100,100} :
		QPoint{100,100};
	setGeometry(position.x(),
				position.y(),
				nameColumnWidth + valueColumnWidth + verticalHeader()->width(),
				rowCount * rowHeight + horizontalHeader()->height() + 5);
	setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	setWindowTitle(DEFAULT_TITLE);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void SettingsEditor::setDefaultOptions() {
	setWordWrap(false);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void SettingsEditor::setDefaultStyleSheet() {
	setStyleSheet(
		"color: rgb(190, 190, 190); \
		background-color: rgb(40,40,40);");
	horizontalHeader()->setStyleSheet(
		"QHeaderView::section{ \
			background-color: rgb(75,75,75); \
			color: rgb(190,190,190);}");
	verticalHeader()->setStyleSheet(
		"QHeaderView::section{ \
			background-color: rgb(75,75,75); \
			color: rgb(190,190,190);}");
}

///////////////////////////////////////////////////////////////////////////////////////////////

SettingsEditor::SettingsEditor(QWidget * parent):
	QTableView(parent),
	settingsManager(nullptr),
	model(nullptr)
{
	setDefaultOptions();
	setDefaultStyleSheet();
}

SettingsEditor::SettingsEditor(SettingsManager* settingsManager, QWidget * parent):
	QTableView(parent),
	settingsManager(settingsManager),
	model(new SettingsTableModel(settingsManager))
{
	setModel(model);
	setDefaultOptions();
	initializeGeometry();
	setDefaultStyleSheet();
}

///////////////////////////////////////////////////////////////////////////////////////////////

SettingsEditor::~SettingsEditor() {
	delete model;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void SettingsEditor::setSettingsManager(SettingsManager * settingsManager) {
	this->settingsManager = settingsManager;
	delete model;
	model = new SettingsTableModel(settingsManager);
	setModel(model);
	initializeGeometry();
}

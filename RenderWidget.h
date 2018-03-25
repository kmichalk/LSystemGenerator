#pragma once

#include "../ui_RenderWidget.h"
#include "PlotRenderer.h"
#include "GrammarComputer.h"
#include "qwidget.h"
#include "GrammarParser.h"
#include "SettingsUser.h"

class RenderWidget: public QWidget, public SettingsUser
{
	Q_OBJECT;

	Ui_RenderWidget ui;
	PlotRenderer* renderer;
	GrammarComputer* grammarComputer;
	QString renderDirectory;
	QTextEdit* grammarEditor;
	GrammarParser* parser;

	void connectSignals();
	QPixmap crop(QPixmap const& p) const;

	SETTINGS(
		(bool, autoCrop, true),
		(QColor, renderBackgroundColor, QColor(0,0,0))
	);

public:
	RenderWidget(QWidget* parent = Q_NULLPTR);
	~RenderWidget();
	void setRenderDirectory(QString dir);
	void setRenderer(PlotRenderer* renderer);
	void setGrammarEditor(QTextEdit* editor);
	void setGrammarParser(GrammarParser* parser);
	//void setGrammarComputer(GrammarComputer* grammarComputer);
	void setGrammar(Grammar* grammar);

public slots:
	void on_renderButton_clicked();
	void on_autoCropCheckBox_stateChanged(int state);
};

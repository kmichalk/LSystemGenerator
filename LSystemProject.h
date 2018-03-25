#pragma once

#include <QtWidgets/QMainWindow>
#include "GeneratedFiles\ui_LSystemProject.h"
#include "qpainter.h"
#include "GeometricActionMap.h"
#include "GrammarParser.h"
#include "GrammarComputer.h"
#include "SettingsEditor.h"
#include "RenderWidget.h"
#include "timer.h"
#include "Statistics.h"

class LSystemProject : public QMainWindow, public SettingsUser
{
	Q_OBJECT;

	Ui::MainWindow ui;
	GeometricActionMap geometricActionMap;
	GrammarParser grammarParser;
	GrammarComputer grammarComputer;
	SettingsManager globalSettings;
	ZoomHandler zoomHandler;
	SettingsEditor settingseEditor;
	RenderWidget renderWidget;
	x::timer<> renderTimer;
	x::timer<> computeTimer;
	Statistics statistics;

	SETTINGS(
		(QString, saveDirectory, "C:\\Users\\user\\Desktop\\lsystem"),
		(QString, openDirectory, "C:\\Users\\user\\Desktop\\lsystem"),
		(QString, renderDirectory, "C:\\Users\\user\\Desktop\\lsystem\\render")
	);

	void compute();
	void connectSignals();
	void generateStatisticsInfo();
	//void setDefaultSettings();

public:
	LSystemProject(QWidget *parent = Q_NULLPTR);
	~LSystemProject();
	virtual void paintEvent(QPaintEvent* event) override;

public slots:
	void on_computeButton_clicked();
	void on_openFileButton_clicked();
	void on_saveFileButton_clicked();
	void on_outputButton_clicked();
	void on_settingsButton_clicked();
	void on_zoomSlider_sliderMoved(int pos);
	void on_plot_scrolled(int delta);
	void on_stepModeCheckBox_stateChanged(int state);
	void on_extrasCheckBox_stateChanged(int state);
	void on_renderButton_clicked();
};

#pragma once

class Plot;

class ZoomHandler
{
	Plot* plot;
	int sliderMax;
	int sliderZeroPos;
	float scaleMin;
	float scaleMax;
	float a;
	float b;
	float c;
	float D;
	float p;
	float q;
	float x1;
	float x2;

	void computeParameters();

public:
	ZoomHandler(Plot* plot = nullptr);
	//ZoomHandler(int sliderMax, float scaleMin, float ScaleMax);
	~ZoomHandler();

	float computeScale(int sliderPos) const;
	void setPlot(Plot* plot);
	void setParameters(int sliderMax, int sliderZeroPos, float scaleMin, float scaleMax);
	void processZoom(int sliderPos) const;
};


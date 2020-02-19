#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include <QBoxLayout>

#include "Iir.h"
#include <Iir.h>

// #include "adcreader.h"
using namespace std;
// class definition 'Window'
class Window : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

public:


	Window(); // default constructor - called when a Window is declared without arguments

	~Window();

     void timerEvent( QTimerEvent * );

public slots:
	void setGain(double gain);

// internal variables for the window class
private:



	QwtKnob      *knob;
	QwtPlot      *plot1;
	QwtPlotCurve *curve1;
	QwtPlot      *plot2;
	QwtPlotCurve *curve2;


	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *vLayout;  // vertical layout
	QHBoxLayout  *hLayout;  // horizontal layout

	static const int plotDataSize = 100;

	// data arrays for the plot
	double xData1[plotDataSize];
	double yData1[plotDataSize];
	double xData2[plotDataSize];
	double yData2[plotDataSize];
	double xData3[plotDataSize];
	double yData3[plotDataSize];


	double gain;
	int count;




//	ADCreader *adcreader;
};

#endif // WINDOW_H

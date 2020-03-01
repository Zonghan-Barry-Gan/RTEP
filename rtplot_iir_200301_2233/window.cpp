#include "window.h"
// #include "adcreader.h"
#include "Iir.h"
#include <Iir.h>

#include <cmath>  // for sine stuff


 using namespace std;
 //set filter
 const int order = 40;

 // sampling rate here 1kHz as an example
 const float samplingrate = 1000;

 const quint16 sderprt = 1117;
 const quint16 rscverprt = 1112;

 FILE *florigin = NULL;
 FILE *flhp1 = NULL;
 Iir::Butterworth::HighPass<order> hp1;

Window::Window() : gain(2), count(0)
{
	knob = new QwtKnob;

	// set up the gain knob
	knob->setValue(gain);

	
	// use the Qt signals/slots framework to update the gain -
	// every time the knob is moved, the setGain function will be called
	connect( knob, SIGNAL(valueChanged(double)), SLOT(setGain(double)) );
	connect( knob, SIGNAL(valueChanged(double)), SLOT(setGain(double)) );
      


	// set up the initial plot data
	for( int index=0; index<plotDataSize; ++index )
	{
		xData1[index] = index;
        yData1[index] = 0;
		xData2[index] = index;
        yData2[index] = 0;
		xData3[index] = index;
        yData3[index] = 0;
		
		
	}

	curve1 = new QwtPlotCurve;
	curve2 = new QwtPlotCurve;
//	curve3 = new QwtPlotCurve;
	plot1 = new QwtPlot;
	plot2 = new QwtPlot;
	// make a plot curve from the data and attach it to the plot
	curve1->setSamples(xData1, yData1, plotDataSize);
	curve1->attach(plot1);
    //curve3->setSamples(xData3, yData3, plotDataSize);
    //curve3->attach(plot1);
	curve2->setSamples(xData2, yData2, plotDataSize);
	curve2->attach(plot2);

	plot1->replot();
	plot1->show();
	plot2->replot();
	plot2->show();



	// set up the layout - knob above thermometer
	vLayout = new QVBoxLayout;
	vLayout->addWidget(knob);

	// plot to the left of knob and thermometer
	hLayout = new QHBoxLayout;
	hLayout->addLayout(vLayout);
	hLayout->addWidget(plot1);
	hLayout->addWidget(plot2);
	setLayout(hLayout);

	// This is a demo for a thread which can be
	// used to read from the ADC asynchronously.
	// At the moment it doesn't do anything else than
	// running in an endless loop and which prints out "tick"
	// every second.
//	adcreader = new ADCreader();
//	adcreader->start();



    // Butterworth lowpass

    const float cutoff_frequency = 50; // Hz
    const float passband_gain = 10; // db
    hp1.setup (samplingrate, cutoff_frequency);


    //create file to log data
    flhp1 = fopen("flhp1ed.dat","wt");
    florigin = fopen("origin.dat","wt");



    //initialize UDP sender
    sdersc= new QUdpSocket;
    //bind local address and check
    //if(sdersc.bind(QHostAddress("192.168.43.231"), sderprt)>0);
    if(sdersc->bind(QHostAddress::LocalHost, sderprt)>0);
        qDebug()<<"sender sc bind sucess";
}

Window::~Window() {
	// tells the thread to no longer run its endless loop
//	adcreader->quit();
	// wait until the run method has terminated
//	adcreader->wait();
//	delete adcreader;

    //close the file writing
    fclose(florigin);
    fclose(flhp1);
}

void Window::timerEvent( QTimerEvent * )
{
  //v=adcreader.read();
  double inVal1 = gain * (sin(2*2.0 * M_PI  *count)+sin(10*2.0 * M_PI  *count)+sin(20*2.0 * M_PI  *count)+sin(30*2.0 * M_PI  *count)+sin(40*2.0 * M_PI  *count)+sin(50*2.0 * M_PI  *count)+sin(60*2.0 * M_PI  *count)+sin(70*2.0 * M_PI  *count)+sin(80*2.0 * M_PI  *count)+sin(90*2.0 * M_PI  *count)+sin(100*2.0 * M_PI  *count)+sin(200*2.0 * M_PI  *count));
// this would be the filtered data
  double inVal2 = hp1.filter(inVal1);
  QByteArray msg;
  msg.setNum(inVal2);
  bool cktp;
  const float outval= msg.toFloat(&cktp);
  if (!cktp and outval != inVal2) qDebug() << "before sending data, data type Conversion failed";
  qDebug() << "--- Sending";
  qDebug() << "data: " << msg;
//       qDebug() << "sendingtest " << msg;
  qDebug() << "sendingtest " << outval;
  //send and check
//        bool cksd = sdersc.writeDatagram(msg, QHostAddress("192.168.43.30"), rscverprt);
  bool cksd = sdersc->writeDatagram(msg, QHostAddress("127.0.0.1"), rscverprt);
  //bool cksd = sdersc.writeDatagram(msg, QHostAddress::AnyIPv4, 1112);
  //bool cksd = sdersc.writeDatagram(msg, QHostAddress::LocalHost, 1112);
  if(cksd>0)
      qDebug()<<"successfully send";
  else
  {
  //see the fail reason with error()
      qDebug()<<"sending is failed";
      qDebug()<<sdersc->error();

  }

  fprintf(florigin,"%e\n",inVal1);
  fprintf(flhp1,"%e\n",inVal2);

	// add the new input to the plot
	memmove( yData1, yData1+1, (plotDataSize-1) * sizeof(double) );
	yData1[plotDataSize-1] = inVal1;
	curve1->setSamples(xData1, yData1, plotDataSize);
	plot1->replot();
	
	memmove( yData2, yData2+1, (plotDataSize-1) * sizeof(double) );
	yData2[plotDataSize-1] = inVal2;
	curve2->setSamples(xData2, yData2, plotDataSize);
	plot2->replot();
    ++count;
//	memmove( yData3, yData3+1, (plotDataSize-1) * sizeof(double) );
//	yData3[plotDataSize-1] = inVal3;
//	curve3->setSamples(xData3, yData3, plotDataSize);
//	plot2->replot();
}


// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
	// for example purposes just change the amplitude of the generated input
	this->gain = gain;
}

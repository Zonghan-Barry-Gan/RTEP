#include "Iir.h"

#include <stdio.h>

#include "assert_print.h"

int main (int,char**)
{
	// create 3rd order filter
	Iir::Butterworth::HighPass<3> f;

	// our sample
	const float samplingrate = 1000; // Hz
	const float cutoff_frequency = 55; // Hz

	// settin the coefficients
	femg.setup (samplingrate, cutoff_frequency);
	
//test, assume fs=1000, 10s of signal, then 10000data, there is a signal 100hz,which means peak every 0.01s, every 100 samples, abs = 0.2/(4.096/32768)= 1600
// an interference 50hz, which means peak every 0.02s, every 200 samples, abs = 0.5/(4.096/32768)= 4000
	double b = 0;
	double b2 = 0;
	for(int i=0;i<10000;i++) 
	{
		float a=0;
		if (i%100 == 0) a = 1600;
		if (i%200 == 0) a = 4000+1600;
		b2 = b;
		b = femg.filter(a);
		assert_print(!isnan(b),"HighPass output is NAN\n");
		if ((i>20) && (i<100))
			assert_print((b != 0) || (b2 != 0),
				     "HighPass output is zero\n");
	}
	assert_print(fabs(b) < 1E-25,"HighPass value for t->inf to high!");

	while(1)
	{
		int i = 0;
		float *inData;
		float *outData;
		*inData = ? ;
		*outData[i] = femg.filter(*inData[i]);
		if (getch() == 'p')break;

	}




}

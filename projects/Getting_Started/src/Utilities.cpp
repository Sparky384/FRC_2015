/*
 * Utilities.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: FRC812
 */

// Various utility functions

#include <cmath>

double PwrLimit(double pwr, double limitLow, double limitHigh)
{
	double safeLow, safeHigh;

	if(limitLow >= limitHigh)
		return 0.0;

	safeLow = limitLow   <= -1.0 ? -1.0 : limitLow  > 0 ? 0 : limitLow;
	safeHigh = limitHigh >= 1.0  ?  1.0 : limitHigh < 0 ? 0 : limitHigh;

	return pwr >= safeHigh ? safeHigh : pwr <= safeLow ? safeLow : pwr;
};


double Linearize( double x )
{
	const double linearCoeffA =  4.5505;
	const double linearCoeffB = -5.9762;
	const double linearCoeffC =  2.5895;
	const double linearCoeffD = -0.0869;
	const double linearCoeffE =  0.0913;

	if (fabs(x) < 0.01) {
		x = 0.0;
	}
	if( x > 0.0 ) {
		return 	linearCoeffA*pow(x,4) + linearCoeffB*pow(x,3) +
				linearCoeffC*pow(x,2) + linearCoeffD*x +
				linearCoeffE;
	} else if( x < 0.0) {
		return -Linearize(-x);
	} else {
		return 0.0;
	}
};

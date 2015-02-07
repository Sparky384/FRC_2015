/*
 * Utilities.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: FRC812
 */

// Various utility functions

double PwmLimit(double pwm)
{
	return pwm >= 1.0 ? 1.0 : pwm <= -1.0 ? -1.0 : pwm;
};




#include "WPILib.h"
#include "RPMSource.h"

RpmSource::RpmSource()
{
	this->rpm = 0;
}

void RpmSource::inputRpm(double desiredRpm)
{
	this->rpm = desiredRpm;
}

double RpmSource::PIDGet()
{
	return this->rpm;
}

#ifndef RPMSOURCE_H
#define RPMSOURCE_H

#include "WPILib.h"

class RpmSource : public PIDSource
{
public:
	RpmSource();
	double PIDGet();
	void inputRpm(double desiredRpm);
private:
	double rpm;
};


#endif

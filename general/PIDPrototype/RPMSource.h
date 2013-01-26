#ifndef RPMSOURCE_H
#define RPMSOURCE_H

#include "WPILib.h"

class RPMSource : public PIDSource
{
public:
	RPMSource();
	virtual ~RPMSource();
	void inputRPM(double input);
	double PIDGet();
private:
	double rpm;
};


#endif

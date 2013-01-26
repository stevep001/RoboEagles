#ifndef LOGGINGPIDOUTPUT_H
#define LOGGINGPIDOUTPUT_H

#include "WPILib.h"

class LoggingPIDOutput : public PIDOutput
{
public:
	LoggingPIDOutput(PIDOutput *output);
	virtual ~LoggingPIDOutput();
	void PIDWrite(float output);
private:
	PIDOutput *wrappedOutput;
};


#endif

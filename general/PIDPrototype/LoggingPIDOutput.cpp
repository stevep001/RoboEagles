#include "WPILib.h"
#include "LoggingPIDOutput.h"

LoggingPIDOutput::LoggingPIDOutput(PIDOutput *pidOutput)
{
	wrappedOutput = pidOutput;
}

LoggingPIDOutput::~LoggingPIDOutput()
{
	delete wrappedOutput;
}

void LoggingPIDOutput::PIDWrite(float output)
{
	printf("value is %f\n", output);
	wrappedOutput->PIDWrite(output);
}

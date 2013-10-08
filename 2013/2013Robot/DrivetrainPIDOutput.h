#ifndef DRIVERTRAIN_PID_OUTPUT
#define DRIVERTRAIN_PID_OUTPUT

#include "WPILib.h"

class DrivetrainPIDOutput : public PIDOutput{
private:
	RobotDrive *drive;
public:
	DrivetrainPIDOutput(RobotDrive *chasisRobotDrive);
	void PIDWrite(float output);
};

#endif

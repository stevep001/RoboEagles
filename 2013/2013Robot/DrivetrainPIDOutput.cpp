#include "DrivetrainPIDOutput.h"

DrivetrainPIDOutput::DrivetrainPIDOutput(RobotDrive *chassisRobotDrive) {
	printf("[DrivetrainPIDOutput] Is Going to be constucted\n");
	this->drive = chassisRobotDrive;
	printf("[DrivetrainPIDOutput] Is has been constucted\n");
}

void DrivetrainPIDOutput::PIDWrite(float output) {
	//printf("[DrivetrainPIDOutput] PID Write: L %f, R %f\n", -output, output);
	this->drive->TankDrive(-output, output);
}

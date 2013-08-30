#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Chassis: public Subsystem {
private:
	RobotDrive *drive;
	SpeedController *leftMotor;
	SpeedController *rightMotor;
	
public:
	Chassis();
	void InitDefaultCommand();
	void Stop();
	void TurnLeft(float rate);
	void TurnRight(float rate);
	void Drive(Joystick *stick);
	void MoveForward(float rate);
	void TankDrive(float rateLeft, float rateRight);
	RobotDrive *GetRobotDrive();
	SpeedController *GetLeftMotor();
	SpeedController *GetRightMotor();
};

#endif

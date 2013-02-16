#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	RobotDrive *drive;
	
public:
	Chassis();
	void InitDefaultCommand();
	void Stop();
	void TurnLeft(float rate);
	void TurnRight(float rate);
	void Drive(Joystick *stick);
	void MoveForward(float rate);
};

#endif

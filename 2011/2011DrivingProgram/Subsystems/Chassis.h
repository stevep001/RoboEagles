#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class Chassis: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	RobotDrive *drive;
public:
	Chassis();
	void InitDefaultCommand();
	void goStraight();
	void turnLeft();
	void tankDrive(double left, double right);
	void driveWithJoystick(Joystick *stick);
	void driveWithKinectStick(KinectStick *stick);
};

#endif

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
	DigitalOutput *leftCoastBrakeOutput;
	DigitalOutput *rightCoastBrakeOutput;
	
public:
	Chassis();
	void InitDefaultCommand();
	void enableBrakeMode();
	void disableBrakeMode();
	void goStraight(float rate);
	void turnLeft(float rate);
	void turnRight(float rate);
	void stop();
	void tankDrive(double left, double right);
	void driveWithJoystick(Joystick *stick);
	void driveWithKinectStick(KinectStick *stick);
	void Chassis::MakeJoystickDriveDefault();
	void Chassis::MakeRampDriveDefault();
};

#endif

#ifndef CHASSISSUBSYSTEM_H
#define CHASSISSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class ChassisSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	SpeedController *leftMotor;
	SpeedController *rightMotor;
	RobotDrive *drive;
public:
	ChassisSubsystem();
	void InitDefaultCommand();
	void Drive(Joystick *stick);
	void Stop();

};

#endif

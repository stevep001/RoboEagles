#ifndef EXAMPLE_SUBSYSTEM_H
#define EXAMPLE_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class PrototypingSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Jaguar *motor;
	Encoder *motorEncoder;
public:
	PrototypingSubsystem();
	void InitDefaultCommand();
	Jaguar* GetMotor();
	Encoder* GetMotorEncoder();
};

#endif

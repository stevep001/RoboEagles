#ifndef THROWERSUBSYSTEM_H
#define THROWERSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class ThrowerSubsystem: public Subsystem {
private:
	Solenoid *throwSolenoidOut;
	Solenoid *throwSolenoidIn;
	Jaguar *aimMotor;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	ThrowerSubsystem();
	void InitDefaultCommand();
	void ThrowerSubsystem::Move(double movement);
	void ThrowerSubsystem::StartThrow();
	void ThrowerSubsystem::StopThrow();
	void ThrowerSubsystem::Retract();
};

#endif

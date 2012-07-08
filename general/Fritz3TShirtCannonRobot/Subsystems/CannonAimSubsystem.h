#ifndef CANNONFIRESUBSYSTEM_H
#define CANNONFIRESUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class CannonAimSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Solenoid *downSolenoid;
	Solenoid *upSolenoid;
public:
	CannonAimSubsystem();
	void InitDefaultCommand();
	void CannonAimSubsystem::Down();
	void CannonAimSubsystem::Up();
	void CannonAimSubsystem::Stop();
};

#endif

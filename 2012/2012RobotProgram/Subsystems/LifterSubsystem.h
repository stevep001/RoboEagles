#ifndef FRONTLIFTERSUBSYSTEM_H
#define FRONTLIFTERSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class LifterSubsystem: public Subsystem {
private:
	Solenoid *lifterSolenoidDown;
	Solenoid *lifterSolenoidUp;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	LifterSubsystem();
	void InitDefaultCommand();
	void LifterSubsystem::LiftUp();
	void LifterSubsystem::LiftDown();
	void LifterSubsystem::LiftStop();
};

#endif

#ifndef CANNONSUBSYSTEM_H
#define CANNONSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class CannonSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Solenoid *fillSolenoid;
	Solenoid *fireSolenoid;
public:
	CannonSubsystem();
	void InitDefaultCommand();
	
	void Fill();
	void Fire();
	void Stop();
};

#endif

#ifndef THROWERSUBSYSTEM_H
#define THROWERSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author nowireless
 */
class ThrowerSubsystem: public Subsystem {
private:
	DoubleSolenoid *throwerSolenoid;
	DoubleSolenoid *secThrowerSolenoid;
public:
	ThrowerSubsystem();
	void InitDefaultCommand();
	void Open();
	void Close();
	void Stop();
};

#endif

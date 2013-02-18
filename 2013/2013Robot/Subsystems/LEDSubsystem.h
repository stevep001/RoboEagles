#ifndef LEDSUBSYSTEM_H
#define LEDSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class LEDSubsystem: public Subsystem {
private:
	Solenoid *blueStrip;
	Solenoid *yellowStrip;
	Solenoid *greenRing;
	
	Timer *yellowTimer;
	Timer *blueTimer;
public:
	LEDSubsystem();
	void InitDefaultCommand();
	void Run();
	void SetPizzaBoxActive(bool active);
	void SetShooterActive(bool active);


};

#endif

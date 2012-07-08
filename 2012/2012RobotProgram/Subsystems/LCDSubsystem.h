#ifndef LCDSUBSYSTEM_H
#define LCDSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class LCDSubsystem: public Subsystem {
private:
	DriverStationLCD *lcd;
	
	// true if display needs to be updated on next round, false if not
	bool updateDisplay;
	
	// Currently selected values for things we display
	int autonomousProgram;
	
	// Currently selected throwing power
	int throwingPower;
	
	void UpdateLine1();
	void UpdateLine2();
	void UpdateLine3();
	void UpdateLine4();
public:
	LCDSubsystem();
	void InitDefaultCommand();
	void UpdateAutonomousProgram(int autonomousProgram);
	void UpdateThrowingPower(int throwingPower);
	void Update();
};

#endif

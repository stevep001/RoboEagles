#ifndef LCDDISPLAYSUBSYSTEM_H
#define LCDDISPLAYSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class LcdDisplaySubsystem: public Subsystem {
private:
	bool line1Updated;
	float tiltAngle;
public:
	LcdDisplaySubsystem();
	void InitDefaultCommand();
	void UpdateLines();
	void SetTiltAngle(float tiltAngle);
};

#endif

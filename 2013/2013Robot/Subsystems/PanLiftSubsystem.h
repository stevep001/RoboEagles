#ifndef PANLIFTSUBSYSTEM_H
#define PANLIFTSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class PanLiftSubsystem: public Subsystem {
private:
	SpeedController *panLiftMotor;
public:
	PanLiftSubsystem();
	void InitDefaultCommand();
	void SetSpeed(float speed);
};

#endif

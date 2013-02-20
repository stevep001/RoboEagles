#ifndef PANSUBSYSTEM_H
#define PANSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class PanSubsystem: public Subsystem {
private:
	SpeedController *panIngestBeltMotor;
	SpeedController *panLateralBeltMotor;
public:
	PanSubsystem();
	void InitDefaultCommand();
	void SetIngestBeltSpeed(float speed);
	void SetLateralBeltSpeed(float speed);
};

#endif

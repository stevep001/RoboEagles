#ifndef FRISBEEPANSUBSYSTEM_H
#define FRISBEEPANSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class FrisbeePanSubsystem: public Subsystem {
private:
	SpeedController *panIngestBeltMotor;
	SpeedController *panLateralBeltMotor;
public:
	FrisbeePanSubsystem();
	void InitDefaultCommand();
};

#endif

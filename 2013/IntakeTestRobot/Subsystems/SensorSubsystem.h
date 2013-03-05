#ifndef SENSORSUBSYSTEM_H
#define SENSORSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class SensorSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	
	DigitalInput	*loaderFrisbeeDetector;
	DigitalInput	*loaderLowLimitSwitch;
	Encoder			*panLiftEncoder;
public:
	SensorSubsystem();
	void InitDefaultCommand();
	bool IsFrisbeeInLoader();
	bool IsLoaderAtLowLimit();
	int GetPanLiftEncoderCount();
	Encoder* GetPanLiftEncoder();
};

#endif

#ifndef SENSORSUBSYSTEM_H
#define SENSORSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class SensorSubsystem: public Subsystem {
private:
	Gyro *horizontalGyro;
	DigitalInput *tiltEncoderMagInc;
	DigitalInput *tiltEncoderMagDec;
public:
	SensorSubsystem();
	void InitDefaultCommand();
	float GetHorizontalAngle();
	bool GetTiltEncoderMagDec();
	bool GetTiltEncoderMagInc();
};

#endif

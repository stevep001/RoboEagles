#ifndef SENSORSUBSYSTEM_H
#define SENSORSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class SensorSubsystem: public Subsystem {
private:
	Gyro *horizontalGyro;
	
	// Drive
	Encoder *leftEncoder;
	Encoder *rightEncoder;
	
	// Tilt
	Encoder *tiltEncoder;
	DigitalInput *tiltEncoderMagInc;
	DigitalInput *tiltEncoderMagDec;
	DigitalInput *tiltLowerLimit;
	DigitalInput *tiltUpperLimit;
	
	// Pizza box	
	DigitalInput *topLimitSwitch;
	DigitalInput *botLimitSwitch;
	DigitalInput *upperLimitSwitch;
	DigitalInput *lowerLimitSwitch;
	DigitalInput *kickerLimitSwitch;
	DigitalInput *frisbeeInBoxSwitch;
	
	// Shooter
	Encoder *shooterEncoder;
	
public:
	SensorSubsystem();
	
	void Stop();
	void InitDefaultCommand();
	float GetHorizontalAngle();
	int GetLeftEncoderValue();
	int GetRightEncoderValue();
	
	bool GetTiltEncoderMagDec();
	bool GetTiltEncoderMagInc();
	int GetTiltEncoderValue();
	bool GetTiltLowerLimit();
	bool GetTiltUpperLimit();
	Encoder *GetTiltEncoder();

	int GetShooterEncoderValue();
	bool GetPizzaTopLimitSwitch();
	bool GetPizzaUpperLimitSwitch();
	bool GetPizzaLowerLimitSwitch();
	bool GetPizzaBottomLimitSwitch();
	bool GetKickerLimitSwitch();
	bool GetFrisbeeInBoxSwitch();
};

#endif

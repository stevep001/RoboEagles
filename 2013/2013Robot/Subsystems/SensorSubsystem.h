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
	Encoder *shooterEncoder1;
//	Encoder *shooterEncoder2;
	
	// Frisbee Pan
	DigitalInput	*loaderFrisbeeDetector;
	DigitalInput	*loaderLowLimitSwitch;
	Encoder			*panLiftEncoder;
	
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
	//Encoder *GetTiltEncoder();

	int GetShooterEncoder1Value();
	//int GetShooterEncoder2Value();
	bool GetPizzaTopLimitSwitch();
	bool GetPizzaUpperLimitSwitch();
	bool GetPizzaLowerLimitSwitch();
	bool GetPizzaBottomLimitSwitch();
	bool IsKickerStowed();
	bool IsFrisbeeInBox();
	
	bool IsFrisbeeInLoader();
	bool IsLoaderAtLowLimit();
	int GetPanLiftEncoderCount();
	Encoder* GetPanLiftEncoder();
	
	Encoder *GetLeftDriveEncoder();
	Encoder *GetRightDriveEncoder();
	
	Gyro* GetHorizontalGyro();
};

#endif

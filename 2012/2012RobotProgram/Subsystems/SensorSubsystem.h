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
	UINT32 lastArmPosition;
	Timer *armDebounceTimer;
	DigitalInput *ballSensor1;
	DigitalInput *ballSensor2;
	DigitalInput *ballSensor3;
	DigitalInput *floorTransitionSensor;
	DigitalInput *armPositionSensor;
	ADXL345_SPI *accelerometer;
	Gyro *yawGyro;
	Gyro *pitchGyro;
	AnalogChannel *maxbotics;

public:
	SensorSubsystem();
	void InitDefaultCommand();
	
	bool IsBallPresentSensor1();
	bool IsBallPresentSensor2();
	bool IsBallPresentSensor3();
	
	bool IsFloorDark();
	bool IsArmDown();

	float GetYawGyroAngle();
	float GetPitchGyroAngle();
	
	float SensorSubsystem::GetRangefinderDistanceInInches();
};

#endif

#ifndef SHOOTERTILTSUBSYSTEM_H
#define SHOOTERTILTSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class ShooterTiltSubsystem: public Subsystem {
private:
	Jaguar *tiltJaguar;
	PIDController *pidController;
	
	float currentAngle;
public:
	ShooterTiltSubsystem();
	void InitDefaultCommand();
	void SetAngle(float desiredAngle);
	void IncreaseTilt(float amountToIncrease);
	void DecreaseTilt(float amountToDecrease);
	void Stop();
	Encoder *GetEncoder();
	Jaguar *GetMotor();
};

#endif

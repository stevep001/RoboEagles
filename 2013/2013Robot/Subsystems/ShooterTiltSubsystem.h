#ifndef SHOOTERTILTSUBSYSTEM_H
#define SHOOTERTILTSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "Commands/PIDSubsystem.h"
#include "PIDController.h"
#include "float.h"
#include "WPILib.h"

// Tilt angle is defined with reference to standing on the stand.
#define MIN_TILT_ANGLE	0
// 
#define MAX_TILT_ANGLE	75

/**
 *
 *
 * @author speterson
 */
class ShooterTiltSubsystem: public PIDSubsystem {
public:
	enum ShooterTiltMode {
		/*
		 * Indicates that the tilt subsystem is initializing.  This will seek to the low limit
		 * to calibrate our zero point.
		 */
			Initializing,
			/*
			 * System is running.
			 */
			Running,
			/*
			 * Indicates there was a calibration issue and the system is not running.
			 */
			CalibrationError,
			/*
			 * Indicates that high limit was reached
			 */
			HighLimitError
		};
private:
	SpeedController *tiltMotor;
	float currentAngle;
	ShooterTiltMode mode;
	Encoder *tiltEncoder;
	
	static const double pGain = 0.0025;
	static const double iGain = 0.0009;
	static const double dGain = 0.0015;
public:
	ShooterTiltSubsystem();
	void InitDefaultCommand();
	void SetAngle(float desiredAngle);
	float GetAngle();

	void IncreaseTilt(float amountToIncrease);
	void DecreaseTilt(float amountToDecrease);
	
	SpeedController *GetMotor();
	
	ShooterTiltSubsystem::ShooterTiltMode GetMode();
	void SetMode(ShooterTiltSubsystem::ShooterTiltMode mode);
	
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	
	PIDController *GetTiltPIDController();
	Encoder *GetTiltEncoder();
};

#endif

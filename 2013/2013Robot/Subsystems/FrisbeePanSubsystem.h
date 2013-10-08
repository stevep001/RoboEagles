#ifndef FRISBEEPANSUBSYSTEM_H
#define FRISBEEPANSUBSYSTEM_H
#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include "SensorSubsystem.h"

/**
 *
 *
 * @author speterson
 */
class FrisbeePanSubsystem: public PIDSubsystem {
public:
	enum FrisbeePanMode {
		Pickup,
		Ingest,
		Load,
		RunLoad,
		ExitLoad,
		EnteringCalibration,
		Calibrating,
		Stow,
		RunStow
	};
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	SpeedController *panIngestBeltMotor;
	SpeedController *panLateralBeltMotor;
	SpeedController *panTiltMotor;
	FrisbeePanMode mode;
	SensorSubsystem *sensorSubsystem;
	int initializationCount;
public:
	FrisbeePanSubsystem(SensorSubsystem *sensorSubsystem);
	void InitDefaultCommand();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void UpPanTilt();
	void StopPanTilt();
	void RunIntake();
	void StopIntake();
	void StowPan();
	void DeployPan();
	void SetMode(FrisbeePanMode mode);
	SpeedController *GetLiftMotor();
	FrisbeePanMode GetMode();
	
	PIDController *GetPanTiltPIDController();
};

#endif

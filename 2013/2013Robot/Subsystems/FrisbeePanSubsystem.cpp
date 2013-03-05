#include "FrisbeePanSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/FrisbeePanSupervisorCommand.h"

#define PAN_LIFT_POWER	(-.8)


#define	PAN_INGEST_POWER	(.5)
#define	PAN_LATERAL_POWER	(.4)

// Encoder counts for various 
#define	INGEST_COUNT	80
#define LOAD_COUNT		120


FrisbeePanSubsystem::FrisbeePanSubsystem(SensorSubsystem *sensorSubsystem) : Subsystem("FrisbeePanSubsystem") {
	printf("FrisbeePanSubsystem:: constructor started\n");
	this->panIngestBeltMotor = new Jaguar(PWM_SLOT, PAN_INGEST_BELT_MOTOR);
	this->panLateralBeltMotor = new Jaguar(PWM_SLOT, PAN_LATERAL_BELT_MOTOR);
	this->panTiltMotor = new Jaguar(PWM_SLOT, PAN_LIFT_MOTOR);
	this->sensorSubsystem = sensorSubsystem;
	this->initializationCount = 0;
	printf("FrisbeePanSubsystem:: constructor started\n");
}
    
void FrisbeePanSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new FrisbeePanSupervisorCommand());
}

SpeedController *FrisbeePanSubsystem::GetLiftMotor()
{
	return this->panTiltMotor;
}

void FrisbeePanSubsystem::DeployPan()
{
	this->SetMode(FrisbeePanSubsystem::EnteringCalibration);
}

void FrisbeePanSubsystem::StowPan()
{
	this->SetMode(FrisbeePanSubsystem::Stow);
}

void FrisbeePanSubsystem::UpPanTilt()
{
	this->panTiltMotor->Set(PAN_LIFT_POWER);
}

void FrisbeePanSubsystem::StopPanTilt()
{
	this->panTiltMotor->Set(0);
}

void FrisbeePanSubsystem::RunIntake()
{
	this->panLateralBeltMotor->Set(PAN_LATERAL_POWER);
	this->panIngestBeltMotor->Set(PAN_INGEST_POWER);
}

void FrisbeePanSubsystem::StopIntake()
{
	this->panLateralBeltMotor->Set(0);
	this->panIngestBeltMotor->Set(0);
}

void FrisbeePanSubsystem::SetMode(FrisbeePanMode mode)
{
	this->mode = mode;
}

FrisbeePanSubsystem::FrisbeePanMode FrisbeePanSubsystem::GetMode()
{
	return this->mode;
}

#include "PanSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/PanSupervisorCommand.h"

PanSubsystem::PanSubsystem() : Subsystem("PanSubsystem") {
	this->panIngestBeltMotor = new Jaguar(PWM_SLOT, PAN_INGEST_BELT_MOTOR);
	this->panLateralBeltMotor = new Jaguar(PWM_SLOT, PAN_LATERAL_BELT_MOTOR);
}
    
void PanSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new PanSupervisorCommand());
}

void PanSubsystem::SetIngestBeltSpeed(float speed)
{
	this->panIngestBeltMotor->Set(speed);
}

void PanSubsystem::SetLateralBeltSpeed(float speed)
{
	this->panLateralBeltMotor->Set(speed);
}

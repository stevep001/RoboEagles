#include "KickerSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/KickerSupervisorCommand.h"

KickerSubsystem::KickerSubsystem(PizzaBoxSubsystem *pizzaBoxSubsystem, SensorSubsystem *sensorSubsystem) : Subsystem("KickerSubsystem") {
	printf("KickerSubsystem: constructor started.\n");
	this->kickerMotor = new Jaguar(PWM_SLOT, KICKER_MOTOR);
	this->kickerState = KickerSubsystem::Initializing;
	this->pizzaBoxSubsystem = pizzaBoxSubsystem;
	this->sensorSubsystem = sensorSubsystem;
	printf("KickerSubsystem: constructor completed.\n");

}
    
void KickerSubsystem::InitDefaultCommand() {
	this->SetDefaultCommand(new KickerSupervisorCommand());
}

// Only called by KickerSupervisorCommand
void KickerSubsystem::SetSpeed(float speed)
{
	this->kickerMotor->Set(speed);
}

// Only called by KickerSupervisorCommand
void KickerSubsystem::SetKickerState(KickerSubsystem::KickerState newState)
{
	this->kickerState = newState;
}

// Only called by KickerSupervisorCommand
KickerSubsystem::KickerState KickerSubsystem::GetKickerState()
{
	return this->kickerState;
}

// This is used by other commands to tell the subsystem to start doing something.
void KickerSubsystem::Kick()
{
	if (this->pizzaBoxSubsystem->IsInFiringPosition() && this->CanKick())
	{
		printf("KickerSubsystem: Kick!\n");
		this->kickerState = KickerSubsystem::KickingWaitingForSwitchOff;
	}
	else
	{
		printf("KickerSubsystem: Someone requested a kick but not in firing position or kicker is moving\n");
	}
}

bool KickerSubsystem::CanKick()
{
	return this->kickerState == Stowed;
}

bool KickerSubsystem::IsStowed()
{
	return this->kickerState == Stowed;
}

#include "PizzaBoxSubsystem.h"
#include "../Robotmap.h"
#include "../CommandBase.h"
#include "../Commands/PizzaBoxSupervisorCommand.h"

// Speed values for the motor
#define MOTOR_SPEED_UP 0.3
#define MOTOR_SPEED_DOWN -(0.3)

/*
 * This subsystem controls the "pizza box" frisbee storage/lifter, teamed with 
 * PizzaBoxSupervisorCommand for higher level function.
 * 
 */
PizzaBoxSubsystem::PizzaBoxSubsystem(SensorSubsystem *sensorSubsystem, LEDSubsystem *ledSubsystem) : Subsystem("PizzaBoxSubsystem") {
	printf("PizzaBoxSubsystem: constructor starting\n");
	this->sensorSubsystem = sensorSubsystem;
	this->ledSubsystem = ledSubsystem;
	pizzaBoxMotor = new Jaguar(PWM_SLOT, PIZZA_BOX_MOTOR);

	printf("PizzaBoxSubsystem: constructor completed\n");
}
    
void PizzaBoxSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new PizzaBoxSupervisorCommand());
}

PizzaBoxSubsystem::PizzaBoxState PizzaBoxSubsystem::GetCurrentState()
{
	return this->currentState;
}

void PizzaBoxSubsystem::SetCurrentState(PizzaBoxState newState)
{
	this->currentState = newState;
}

int PizzaBoxSubsystem::GetCurrentPosition()
{
	return this->currentPosition;
}

void PizzaBoxSubsystem::SetCurrentPosition(int newPosition)
{
	this->currentPosition = newPosition;
}

void PizzaBoxSubsystem::MoveFirstLoadingPosition()
{
	this->currentState = MovingToNextLoadingPosition;
	this->currentPosition = 0;
}

void PizzaBoxSubsystem::MoveNextLoadingPosition()
{
	if (this->CanMoveNextLoadingPosition())
	{
		this->currentState = MovingToNextLoadingPosition;
	}
}

void PizzaBoxSubsystem::MoveFirstFiringPosition()
{
	this->currentState = MovingToNextFiringPosition;
	this->currentPosition = 0;
}

void PizzaBoxSubsystem::MoveNextFiringPosition()
{
	if (this->CanMoveNextFiringPosition())
	{
		this->currentState = MovingToNextFiringPosition;
	}
}

bool PizzaBoxSubsystem::IsInLoadingPosition()
{
	return this->currentState == LoadingPosition;
}

bool PizzaBoxSubsystem::CanMoveNextLoadingPosition()
{
	return this->currentState == LoadingPosition && this->currentPosition < MAX_FRISBEES;
}

bool PizzaBoxSubsystem::IsInFiringPosition()
{
	return this->currentState == FiringPosition;
}

bool PizzaBoxSubsystem::FiringSoon()
{
	return this->currentState == FiringPosition || this->currentState == MovingToNextFiringPosition;
}

bool PizzaBoxSubsystem::CanMoveNextFiringPosition()
{
	return this->currentState == FiringPosition && this->currentPosition < MAX_FRISBEES;
}

// Basic controls over subsystem
//
void PizzaBoxSubsystem::MoveTop() {
	if(this->IsAtTopLimit()) {
		this->Stop();
	} else {
		this->MoveUp();
	}
}

void PizzaBoxSubsystem::MoveBottom() {
	if(this->IsAtBottomLimit()) {
		this->Stop();
	} else {
		this->MoveDown();
	}
}

bool PizzaBoxSubsystem::IsAtTopLimit() {
	return CommandBase::sensorSubsystem->GetPizzaTopLimitSwitch();
}

bool PizzaBoxSubsystem::IsAtBottomLimit() {
	return CommandBase::sensorSubsystem->GetPizzaBottomLimitSwitch();
}

bool PizzaBoxSubsystem::IsFiringSwitchOn() {
	return CommandBase::sensorSubsystem->GetPizzaUpperLimitSwitch();
}

bool PizzaBoxSubsystem::IsLoadingSwitchOn() {
	return CommandBase::sensorSubsystem->GetPizzaLowerLimitSwitch();
}

void PizzaBoxSubsystem::Stop() {
	this->pizzaBoxMotor->Set(0);
}

void PizzaBoxSubsystem::MoveUp()
{
	if (this->IsAtTopLimit())
	{
		this->pizzaBoxMotor->Set(0);
	}
	else
	{
		this->pizzaBoxMotor->Set(MOTOR_SPEED_UP);
	}
}

void PizzaBoxSubsystem::MoveDown()
{
	if (this->IsAtBottomLimit())
	{
		this->pizzaBoxMotor->Set(0);
	}
	else
	{
		this->pizzaBoxMotor->Set(MOTOR_SPEED_DOWN);
	}
}

#include "PizzaBoxSubsystem.h"
#include "../Robotmap.h"

// Speed values for the motor
#define MOTOR_SPEED_UP 0.2
#define MOTOR_SPEED_DOWN -0.2

#define MAX_FRISBEES	4

#define WAITING_FOR_LOWER_SWITCH_OFF 1
#define WAITING_FOR_LOWER_SWITCH_ON 2
#define WAITING_FOR_TOP_LIMIT_SWITCH_ON 3
#define WAITING_FOR_UPPER_LIMIT_SWITCH_ON 4
#define WAITING_FOR_UPPER_LIMIT_SWITCH_OFF 5

/*
 * This subsystem controls the "pizza box" frisbee storage/lifter.
 * 
 */

PizzaBoxSubsystem::PizzaBoxSubsystem() : Subsystem("PizzaBoxSubsystem") {
	pizzaBoxMotor = new Jaguar(PIZZA_BOX_MOTOR);
	topLimitSwitch = new DigitalInput(TOP_LIMIT_SWITCH);
	botLimitSwitch = new DigitalInput(BOT_LIMIT_SWITCH);
	upperLimitSwitch = new DigitalInput(UPPER_LIMIT_SWITCH);
	lowerLimitSwitch = new DigitalInput(LOWER_LIMIT_SWITCH);
	PizzaBoxPosition = 1;
	//----------------------------------------------------------------------------------------------
	// Change based on how many we start with
	FrisbeeCount = 0;
	//----------------------------------------------------------------------------------------------
}
    
void PizzaBoxSubsystem::InitDefaultCommand() {
	// None
}

void PizzaBoxSubsystem::SetNumberOfFrisbees(int numberOfFrisbees)
{
	FrisbeeCount = numberOfFrisbees;
}

void PizzaBoxSubsystem::MoveTop() {
	if(this->IsAtTop()) {
		pizzaBoxMotor->Set(0);
		PizzaBoxPosition = 9;
	} else {
		this->MoveUp();
	}
}

void PizzaBoxSubsystem::MoveBottom() {
	if(this->IsAtBottom()) {
		pizzaBoxMotor->Set(0);
		PizzaBoxPosition = 1;
	} else {
		this->MoveDown();
	}
}

void PizzaBoxSubsystem::LoadIndex() {
	if (state == WAITING_FOR_LOWER_SWITCH_OFF)
	{
		if (!this->SwitchLower())
		{
			state = WAITING_FOR_LOWER_SWITCH_ON;
		}
		this->MoveUp();
	}
	else
	{
		if (this->SwitchLower())
		{
			this->Stop();
		}
	}
}

void PizzaBoxSubsystem::StartLoadIndex()
{
	if (this->SwitchLower())
	{
		state = WAITING_FOR_LOWER_SWITCH_OFF;
	} else {
		printf("StartLoadIndex but lower switch is off.");
		state = WAITING_FOR_LOWER_SWITCH_ON;
	}
	pizzaBoxMotor->Set(MOTOR_SPEED_UP);
}

void PizzaBoxSubsystem::FireIndex() {
	// don't forget to reset it once done
}

bool PizzaBoxSubsystem::IsInFiringPosition()
{
	// TODO need to cover this situation when loading
	return this->SwitchUpper();
}
bool PizzaBoxSubsystem::IsInLoadingPosition()
{
	// TODO need to cover this situation when we are shooting
	return this->SwitchLower();
}

void PizzaBoxSubsystem::StartMoveFiring()
{
	printf("Starting move to firing position: ");
	if (!this->IsAtTop())
	{
		state = WAITING_FOR_TOP_LIMIT_SWITCH_ON;
		this->MoveUp();
		printf("Moving up\n");
	}
	else
	{
		state = WAITING_FOR_UPPER_LIMIT_SWITCH_ON;
		this->MoveDown();
		printf("At top, moving down\n");
	}
}

void PizzaBoxSubsystem::MoveFiringPosition()
{
	if (state == WAITING_FOR_TOP_LIMIT_SWITCH_ON)
	{
		if (this->IsAtTop())
		{
			state = WAITING_FOR_UPPER_LIMIT_SWITCH_ON;
			this->MoveDown();
			printf("Reached top, starting move down.\n");
		}
		else
		{
			this->MoveUp();
		}
	}
	else if (state == WAITING_FOR_UPPER_LIMIT_SWITCH_ON)
	{
		if (this->SwitchUpper())
		{
			printf("Saw upper switch, stopping.\n");
			this->Stop();
		}
		else
		{
			this->MoveDown();
		}
	}
	else
	{
		printf("Unexpected state in MoveFiringPosition: %d", state);
		this->Stop();
	}
}



void PizzaBoxSubsystem::Stop() {
	pizzaBoxMotor->Set(0);
}

bool PizzaBoxSubsystem::IsAtTop() {
	return topLimitSwitch->Get() == 0;
}

bool PizzaBoxSubsystem::IsAtBottom() {
	return botLimitSwitch->Get() == 0;
}

bool PizzaBoxSubsystem::SwitchUpper() {
	return upperLimitSwitch->Get() == 0;
}

bool PizzaBoxSubsystem::SwitchLower() {
	return lowerLimitSwitch->Get() == 0;
}

bool PizzaBoxSubsystem::IsBoxFull()
{
	return FrisbeeCount >= MAX_FRISBEES;
}

void PizzaBoxSubsystem::MoveUp()
{
	if (!this->IsAtTop())
	{
		pizzaBoxMotor->Set(MOTOR_SPEED_UP);
	}
}

void PizzaBoxSubsystem::MoveDown()
{
	if (!this->IsAtBottom())
	{
		pizzaBoxMotor->Set(MOTOR_SPEED_DOWN);
	}
}

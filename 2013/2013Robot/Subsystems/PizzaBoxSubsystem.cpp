#include "PizzaBoxSubsystem.h"
#include "../Robotmap.h"

// Speed values for the motor
#define MOTOR_SPEED_UP 0.2
#define MOTOR_SPEED_DOWN -0.2

#define MAX_FRISBEES	4

// These intermediate states are used to track progress toward the
// next position
#define WAITING_FOR_LOWER_SWITCH_OFF 1
#define WAITING_FOR_LOWER_SWITCH_ON 2
#define WAITING_FOR_TOP_LIMIT_SWITCH_ON 3
#define WAITING_FOR_UPPER_LIMIT_SWITCH_ON 4
#define WAITING_FOR_UPPER_LIMIT_SWITCH_OFF 5
#define WAITING_FOR_BOTTOM_LIMIT_SWITCH_ON 6

// Known positions of the pizza box.

// We load in the highest slot first
#define LOAD_POSITION_1	1
#define LOAD_POSITION_2	2
#define	LOAD_POSITION_3	3
#define LOAD_POSITION_4	4

// We shoot from the lowest slot first
#define FIRE_POSITION_1	5
#define	FIRE_POSITION_2	6
#define	FIRE_POSITION_3	7
#define FIRE_POSITION_4	8

// Other positions
#define TOP_POSITION	9
#define	UNKNOWN_POSITION	10

/*
 * This subsystem controls the "pizza box" frisbee storage/lifter.
 * 
 */

PizzaBoxSubsystem::PizzaBoxSubsystem() : Subsystem("PizzaBoxSubsystem") {
	printf("PizzaBoxSubsystem: constructor starting\n");
	pizzaBoxMotor = new Jaguar(PIZZA_BOX_MOTOR);
	frisbeeEjectMotor = new Jaguar(FRISBEE_EJECT_MOTOR);
	topLimitSwitch = new DigitalInput(TOP_LIMIT_SWITCH_SLOT, TOP_LIMIT_SWITCH);
	botLimitSwitch = new DigitalInput(BOT_LIMIT_SWITCH_SLOT, BOT_LIMIT_SWITCH);
	upperLimitSwitch = new DigitalInput(UPPER_LIMIT_SWITCH_SLOT, UPPER_LIMIT_SWITCH);
	lowerLimitSwitch = new DigitalInput(LOWER_LIMIT_SWITCH_SLOT, LOWER_LIMIT_SWITCH);
	
	// If the frisbee shooter is at the top position, we assume it is full.
	// Otherwise it's empty.
	if (this->IsAtTop())
	{
		this->FrisbeeCount = 4;
		this->PizzaBoxPosition = TOP_POSITION;
	}
	else
	{
		this->FrisbeeCount = 0;
		this->PizzaBoxPosition = UNKNOWN_POSITION;
	}
	printf("PizzaBoxSubsystem: constructor completed\n");
}
    
void PizzaBoxSubsystem::InitDefaultCommand() {
}

bool PizzaBoxSubsystem::IsInLoadingPosition()
{
	switch (this->PizzaBoxPosition)
	{
		case LOAD_POSITION_1:
		case LOAD_POSITION_2:
		case LOAD_POSITION_3:
		case LOAD_POSITION_4:
			return true;
		default:
			return false;
	}
}

bool PizzaBoxSubsystem::CanMoveNextLoadingPosition()
{
	switch (this->PizzaBoxPosition)
	{
		case LOAD_POSITION_1:
		case LOAD_POSITION_2:
		case LOAD_POSITION_3:
			return true;
		default:
			return false;
	}
}

void PizzaBoxSubsystem::StartMoveFirstLoadingPosition()
{
	printf("StartMoveFirstLoadingPosition: ");
	if (!this->IsAtBottom())
	{
		this->intermediateState = WAITING_FOR_BOTTOM_LIMIT_SWITCH_ON;
		this->MoveDown();
		printf("Moving to down position\n");
	}
	else
	{
		this->intermediateState = WAITING_FOR_LOWER_SWITCH_ON;
		this->MoveUp();
		printf("At top, moving down to first shooting position\n");
	}}

void PizzaBoxSubsystem::MoveFirstLoadingPosition()
{
	printf("MoveFirstLoadingPosition: ");
	if (this->intermediateState == WAITING_FOR_BOTTOM_LIMIT_SWITCH_ON)
	{
		if (this->IsAtBottom())
		{
			this->intermediateState = WAITING_FOR_LOWER_SWITCH_ON;
			this->MoveUp();
			printf("Reached bottom, starting move up.\n");
		}
		else
		{
			this->MoveDown();
		}
	}
	else if (this->intermediateState == WAITING_FOR_LOWER_SWITCH_ON)
	{
		if (this->SwitchLower())
		{
			printf("Saw lower switch, stopping.\n");
			this->Stop();
			this->PizzaBoxPosition = FIRE_POSITION_1;
		}
		else
		{
			this->MoveUp();
		}
	}
	else
	{
		printf("Unexpected intermediate state: %d", this->intermediateState);
		this->Stop();
	}
}

bool PizzaBoxSubsystem::StartMoveNextLoadingPosition()
{
	printf("StartMoveNextLoadingPosition: ");
	if (this->PizzaBoxPosition == LOAD_POSITION_4)
	{
		printf("Error -- pizza box is already in loading position 4\n");
		// Set this so that the box doesn't move.
		this->intermediateState = WAITING_FOR_LOWER_SWITCH_ON;
		return false;
	}

	printf("Starting move to next loading position\n");
	if (this->SwitchLower())
	{
		this->intermediateState = WAITING_FOR_LOWER_SWITCH_OFF;
	} else {
		// Perhaps the box has been nudged a bit and it is below the limit switch.
		// A crappy way to recover but we'll just wait for the lower switch to come on.
		
		// Maybe we'd be better off giving up here.
		
		printf("StartLoadIndex but lower switch is off.");
		this->intermediateState = WAITING_FOR_LOWER_SWITCH_ON;
	}
	
	pizzaBoxMotor->Set(MOTOR_SPEED_UP);\
	return true;
}

// Called repeated from calling command until we're in position
void PizzaBoxSubsystem::MoveToNextLoadingPosition() {
	printf("MoveToNextLoadingPosition: ");
	if (this->intermediateState == WAITING_FOR_LOWER_SWITCH_OFF)
	{
		if (!this->SwitchLower())
		{
			this->intermediateState = WAITING_FOR_LOWER_SWITCH_ON;
		}
		this->MoveUp();
	}
	else if (this->intermediateState == WAITING_FOR_LOWER_SWITCH_ON)
	{
		// Ahh, yes.  We're there.
		if (this->SwitchLower())
		{
			this->Stop();
			switch (this->PizzaBoxPosition)
			{
				case LOAD_POSITION_1:
					this->PizzaBoxPosition = LOAD_POSITION_2;
					break;
				case LOAD_POSITION_2:
					this->PizzaBoxPosition = LOAD_POSITION_3;
					break;
				case LOAD_POSITION_3:
					this->PizzaBoxPosition = LOAD_POSITION_4;
					break;
				default:
					printf("unknown ending state %d\n", this->PizzaBoxPosition);
					break;
			}
		}
	} else {
		printf("Unknown intermediate state %d\n", this->intermediateState);
		this->Stop();
	}
}

bool PizzaBoxSubsystem::IsInFiringPosition()
{
	switch (this->PizzaBoxPosition)
	{
		case FIRE_POSITION_1:
		case FIRE_POSITION_2:
		case FIRE_POSITION_3:		
		case FIRE_POSITION_4:
			return true;
		default:
			return false;
	}
}

bool PizzaBoxSubsystem::CanMoveNextFiringPosition()
{
	switch (this->PizzaBoxPosition)
	{		case FIRE_POSITION_1:
		case FIRE_POSITION_2:
		case FIRE_POSITION_3:
			return true;
		default:
			return false;
	}
}

// Moving to the first firing position moves through two states.
// First, we move to the top position.
// Then we move down until we reach the first firing position.
void PizzaBoxSubsystem::StartMoveFirstFiringPosition()
{
	printf("StartMoveFirstFiringPosition: ");
	if (!this->IsAtTop())
	{
		this->intermediateState = WAITING_FOR_TOP_LIMIT_SWITCH_ON;
		this->MoveUp();
		printf("Moving to top position\n");
	}
	else
	{
		this->intermediateState = WAITING_FOR_UPPER_LIMIT_SWITCH_ON;
		this->MoveDown();
		printf("At top, moving down to first shooting position\n");
	}
}

void PizzaBoxSubsystem::MoveFirstFiringPosition()
{
	printf("MoveFirstFiringPosition");
	if (this->intermediateState == WAITING_FOR_TOP_LIMIT_SWITCH_ON)
	{
		if (this->IsAtTop())
		{
			this->intermediateState = WAITING_FOR_UPPER_LIMIT_SWITCH_ON;
			this->MoveDown();
			printf("Reached top, starting move down.\n");
		}
		else
		{
			this->MoveUp();
		}
	}
	else if (this->intermediateState == WAITING_FOR_UPPER_LIMIT_SWITCH_ON)
	{
		if (this->SwitchUpper())
		{
			printf("Saw upper switch, stopping.\n");
			this->Stop();
			this->PizzaBoxPosition = FIRE_POSITION_1;
		}
		else
		{
			this->MoveDown();
		}
	}
	else
	{
		printf("Unexpected intermediate state: %d", this->intermediateState);
		this->Stop();
	}
}

bool PizzaBoxSubsystem::StartMoveNextFiringPosition()
{
	switch (this->PizzaBoxPosition)
	{
		case FIRE_POSITION_1:
		case FIRE_POSITION_2:
		case FIRE_POSITION_3:
			if (this->SwitchUpper())
			{
				this->intermediateState = WAITING_FOR_UPPER_LIMIT_SWITCH_OFF;
			}
			else
			{
				printf("StartMoveNextFiringPosition: not in a known position\n");
				this->intermediateState = WAITING_FOR_LOWER_SWITCH_ON;
			}
			this->MoveDown();
			return true;
			break;
		default:
			printf("StartMoveNextFiringPosition: can't move there from %d\n", this->PizzaBoxPosition);
			return false;
			break;
	}
}

void PizzaBoxSubsystem::MoveNextFiringPosition()
{
	if (this->intermediateState == WAITING_FOR_UPPER_LIMIT_SWITCH_OFF)
	{
		if (!this->SwitchUpper())
		{
			this->intermediateState = WAITING_FOR_UPPER_LIMIT_SWITCH_ON;
		}
		this->MoveDown();
	} 
	else if (this->intermediateState == WAITING_FOR_UPPER_LIMIT_SWITCH_ON)
	{
		if (this->SwitchUpper())
		{
			this->Stop();
		}
	}
	else
	{
		printf("MoveNextFiringPosition: Unnown intermediate state: %d\n", this->intermediateState);
	}
}

// Basic controls over subsystem

void PizzaBoxSubsystem::MoveTop() {
	if(this->IsAtTop()) {
		pizzaBoxMotor->Set(0);
		PizzaBoxPosition = TOP_POSITION;
	} else {
		this->MoveUp();
	}
}

void PizzaBoxSubsystem::MoveBottom() {
	if(this->IsAtBottom()) {
		pizzaBoxMotor->Set(0);
		PizzaBoxPosition = LOAD_POSITION_1;
	} else {
		this->MoveDown();
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

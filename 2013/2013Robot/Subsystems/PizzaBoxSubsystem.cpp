#include "PizzaBoxSubsystem.h"
#include "../Robotmap.h"

// Speed values for the motor
#define MOTOR_SPEED_UP 0.2
#define MOTOR_SPEED_DOWN -0.2

/*
 * This subsystem controls the "pizza box" frisbee storage/lifter.
 */

PizzaBoxSubsystem::PizzaBoxSubsystem() : Subsystem("PizzaBoxSubsystem") {
	pizzaBoxMotor = new Jaguar(PIZZA_BOX_MOTOR);
	topLimitSwitch = new DigitalInput(TOP_LIMIT_SWITCH);
	botLimitSwitch = new DigitalInput(BOT_LIMIT_SWITCH);
	upperLimitSwitch = new DigitalInput(UPPER_LIMIT_SWITCH);
	lowerLimitSwitch = new DigitalInput(LOWER_LIMIT_SWITCH);
	frisbeeLimitSwitch = new DigitalInput(FRISBEE_LIMIT_SWITCH);
	PizzaBoxPosition = 1;
	//----------------------------------------------------------------------------------------------
	// Change based on how many we start with
	FrisbeeCount = 3;
	//----------------------------------------------------------------------------------------------
}
    
void PizzaBoxSubsystem::InitDefaultCommand() {
	
}

void PizzaBoxSubsystem::MoveTop() {
	if(this->IsAtTop()) {
		pizzaBoxMotor->Set(0);
		PizzaBoxPosition = 9;
	} else {
		pizzaBoxMotor->Set(MOTOR_SPEED_UP);
	}
}

void PizzaBoxSubsystem::MoveBottom() {
	if(this->IsAtBottom()) {
		pizzaBoxMotor->Set(0);
		PizzaBoxPosition = 1;
	} else {
		pizzaBoxMotor->Set(MOTOR_SPEED_DOWN);
	}
}

void PizzaBoxSubsystem::LoadIndex() {
	
	
	
	
	
		/*
	TempPBPos = PizzaBoxPosition;
	if(this->IsThereAFrisbee()){
		if(this->SwitchLower() and TempPBPos == PizzaBoxPosition) {
			pizzaBoxMotor->Set(MOTOR_SPEED_UP);
			PizzaBoxPosition = PizzaBoxPosition++;
		} else if(PizzaBoxPosition =~ TempPBPos and not this->SwitchLower()) {
			pizzaBoxMotor->Set(MOTOR_SPEED_UP);
		} else if(this->SwitchLower() and PizzaBoxPosition =~ TempPBPos and this->IsThereAFrisbee()) {
			pizzaBoxMotor->Set(MOTOR_SPEED_UP);
		} else if(this->SwitchLower() and PizzaBoxPosition =~ TempPBPos and not this->IsThereAFrisbee()) {
			pizzaBoxMotor->Set(0);
		}
	}
*/		
}

void PizzaBoxSubsystem::FireIndex() {
	// don't forget to reset it once done
}

void PizzaBoxSubsystem::MoveFiringPosition() {
	
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

bool PizzaBoxSubsystem::IsThereAFrisbee() {
	return frisbeeLimitSwitch->Get() == 0;
}

bool PizzaBoxSubsystem::SwitchUpper() {
	return upperLimitSwitch->Get() == 0;
}

bool PizzaBoxSubsystem::SwitchLower() {
	return lowerLimitSwitch->Get() == 0;
}



/*
 * 
	void InitDefaultCommand();
	void MoveTop();  // here for testing but not neccessarily use
	void MoveBottom();
	void LoadIndex();
	void FireIndex();
	void MoveFiringPosition();
 */
// Put methods for controlling this subsystem
// here. Call these from Commands.


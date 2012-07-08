#include "ChangeThrowingPowerCommand.h"
#include "../Subsystems/LCDSubsystem.h"

/**
 * This command controls the variable throwing power.
 */
ChangeThrowingPowerCommand::ChangeThrowingPowerCommand(int amountToChange) {
	this->amountToChange = amountToChange;
}

void ChangeThrowingPowerCommand::Initialize() {	
	throwerPower += amountToChange;
	
	if (throwerPower > MAX_THROWING_POWER)
	{
		throwerPower = MAX_THROWING_POWER;
	}
	
	if (throwerPower < MIN_THROWING_POWER)
	{
		throwerPower = MIN_THROWING_POWER;
	}
	
	printf("Throwing power is %d\n", throwerPower);
	
	lcdSubsystem->UpdateThrowingPower(throwerPower);
	
}

void ChangeThrowingPowerCommand::Execute() {
}

bool ChangeThrowingPowerCommand::IsFinished() {
	return true;
}

void ChangeThrowingPowerCommand::End() {
}

void ChangeThrowingPowerCommand::Interrupted() {
}

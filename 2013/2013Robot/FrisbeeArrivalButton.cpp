#include "WPILib.h"
#include "FrisbeeArrivalButton.h"
#include "CommandBase.h"

FrisbeeArrivalButton::FrisbeeArrivalButton()
{
}

bool FrisbeeArrivalButton::Get()
{
	return CommandBase::sensorSubsystem->IsFrisbeeInBox();
}

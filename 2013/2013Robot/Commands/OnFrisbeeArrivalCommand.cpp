#include "OnFrisbeeArrivalCommand.h"

OnFrisbeeArrivalCommand::OnFrisbeeArrivalCommand() {
}

// Called just before this Command runs the first time
void OnFrisbeeArrivalCommand::Initialize() {
	printf("OnFrisbeeArrivalCommand:  Frisbee arrived - ");
	if (pizzaBoxSubsystem->IsInLoadingPosition()) {
		if (pizzaBoxSubsystem->CanMoveNextLoadingPosition())
		{
			printf("moving to next loading position\n");
			pizzaBoxSubsystem->MoveNextLoadingPosition();
		}
		else
		{
			printf("moving to first firing position\n");
			pizzaBoxSubsystem->MoveFirstFiringPosition();
		}
	}
	else
	{
		printf("Not in loading position - ignoring\n");
	}
}

// Called repeatedly when this Command is scheduled to run
void OnFrisbeeArrivalCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool OnFrisbeeArrivalCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void OnFrisbeeArrivalCommand::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OnFrisbeeArrivalCommand::Interrupted() {
}

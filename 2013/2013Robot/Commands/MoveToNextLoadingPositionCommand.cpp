#include "MoveToNextLoadingPositionCommand.h"

MoveToNextLoadingPositionCommand::MoveToNextLoadingPositionCommand() {

}

// Called just before this Command runs the first time
void MoveToNextLoadingPositionCommand::Initialize() {
	if (pizzaBoxSubsystem->CanMoveNextLoadingPosition())
	{
		pizzaBoxSubsystem->MoveNextLoadingPosition();
	}
	else
	{
		printf("No more loading positions\n");
	}
}

// Called repeatedly when this Command is scheduled to run
void MoveToNextLoadingPositionCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool MoveToNextLoadingPositionCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void MoveToNextLoadingPositionCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveToNextLoadingPositionCommand::Interrupted() {
}

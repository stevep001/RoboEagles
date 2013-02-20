#include "MoveToNextFiringPositionCommand.h"

MoveToNextFiringPositionCommand::MoveToNextFiringPositionCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void MoveToNextFiringPositionCommand::Initialize() {
	if (pizzaBoxSubsystem->CanMoveNextFiringPosition())
	{
		pizzaBoxSubsystem->MoveNextFiringPosition();
	}
	else
	{
		printf("Can't move to next firing position\n");
	}
}

// Called repeatedly when this Command is scheduled to run
void MoveToNextFiringPositionCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool MoveToNextFiringPositionCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void MoveToNextFiringPositionCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveToNextFiringPositionCommand::Interrupted() {
}

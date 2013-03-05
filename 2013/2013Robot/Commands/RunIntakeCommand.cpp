#include "RunIntakeCommand.h"

RunIntakeCommand::RunIntakeCommand() {
}

// Called just before this Command runs the first time
void RunIntakeCommand::Initialize() {
	frisbeePanSubsystem->RunIntake();
}

// Called repeatedly when this Command is scheduled to run
void RunIntakeCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool RunIntakeCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RunIntakeCommand::End() {
	frisbeePanSubsystem->StopIntake();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunIntakeCommand::Interrupted() {
	frisbeePanSubsystem->StopIntake();
}

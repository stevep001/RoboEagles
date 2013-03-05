#include "StowPanCommand.h"

StowPanCommand::StowPanCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void StowPanCommand::Initialize() {
	frisbeePanSubsystem->StowPan();
}

// Called repeatedly when this Command is scheduled to run
void StowPanCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool StowPanCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void StowPanCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StowPanCommand::Interrupted() {
}

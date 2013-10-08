#include "AutoDoNothingCommand.h"

AutoDoNothingCommand::AutoDoNothingCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void AutoDoNothingCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void AutoDoNothingCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDoNothingCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void AutoDoNothingCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDoNothingCommand::Interrupted() {
}

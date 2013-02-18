#include "LedControlCommand.h"

LedControlCommand::LedControlCommand() {
	Requires(ledSubsystem);
}

// Called just before this Command runs the first time
void LedControlCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void LedControlCommand::Execute() {
	ledSubsystem->Run();
}

// Make this return true when this Command no longer needs to run execute()
bool LedControlCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LedControlCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LedControlCommand::Interrupted() {
}

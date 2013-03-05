#include "LcdDisplayCommand.h"

LcdDisplayCommand::LcdDisplayCommand() {
	Requires(lcdDisplaySubsystem);
}

// Called just before this Command runs the first time
void LcdDisplayCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void LcdDisplayCommand::Execute() {
	lcdDisplaySubsystem->UpdateLines();
}

// Make this return true when this Command no longer needs to run execute()
bool LcdDisplayCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LcdDisplayCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LcdDisplayCommand::Interrupted() {
}

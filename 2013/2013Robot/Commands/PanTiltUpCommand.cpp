#include "PanTiltUpCommand.h"

PanTiltUpCommand::PanTiltUpCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void PanTiltUpCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void PanTiltUpCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool PanTiltUpCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void PanTiltUpCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PanTiltUpCommand::Interrupted() {
}

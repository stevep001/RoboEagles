#include "ManualTiltUpCommand.h"

ManualTiltUpCommand::ManualTiltUpCommand() {

}

// Called just before this Command runs the first time
void ManualTiltUpCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void ManualTiltUpCommand::Execute() {
	shooterTiltSubsystem->IncreaseTilt(2);
}

// Make this return true when this Command no longer needs to run execute()
bool ManualTiltUpCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ManualTiltUpCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualTiltUpCommand::Interrupted() {

}

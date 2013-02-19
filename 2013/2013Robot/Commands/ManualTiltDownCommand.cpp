#include "ManualTiltDownCommand.h"

ManualTiltDownCommand::ManualTiltDownCommand() {
	
}

// Called just before this Command runs the first time
void ManualTiltDownCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void ManualTiltDownCommand::Execute() {
	shooterTiltSubsystem->DecreaseTilt(2);	
}

// Make this return true when this Command no longer needs to run execute()
bool ManualTiltDownCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ManualTiltDownCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualTiltDownCommand::Interrupted() {

}

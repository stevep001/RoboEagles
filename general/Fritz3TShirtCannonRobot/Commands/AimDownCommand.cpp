#include "AimDownCommand.h"

AimDownCommand::AimDownCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(cannonAimSubsystem);
}

// Called just before this Command runs the first time
void AimDownCommand::Initialize() {
	cannonAimSubsystem->Down();
}

// Called repeatedly when this Command is scheduled to run
void AimDownCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool AimDownCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AimDownCommand::End() {
	cannonAimSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AimDownCommand::Interrupted() {
	cannonAimSubsystem->Stop();
}

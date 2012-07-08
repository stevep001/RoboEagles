#include "AimUpCommand.h"

AimUpCommand::AimUpCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires (cannonAimSubsystem);
}

// Called just before this Command runs the first time
void AimUpCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void AimUpCommand::Execute() {
	cannonAimSubsystem->Up();
}

// Make this return true when this Command no longer needs to run execute()
bool AimUpCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AimUpCommand::End() {
	cannonAimSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AimUpCommand::Interrupted() {
	cannonAimSubsystem->Stop();
}

#include "FireCannonCommand.h"

FireCannonCommand::FireCannonCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(cannonSubsystem);
}

// Called just before this Command runs the first time
void FireCannonCommand::Initialize() {
	printf("Fire start\n");
	cannonSubsystem->Fire();
}

// Called repeatedly when this Command is scheduled to run
void FireCannonCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool FireCannonCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FireCannonCommand::End() {
	printf("Fire end\n");
	cannonSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FireCannonCommand::Interrupted() {
	printf("Fire interrupted\n");
	cannonSubsystem->Stop();
}

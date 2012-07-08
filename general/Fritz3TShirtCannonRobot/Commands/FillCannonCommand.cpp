#include "FillCannonCommand.h"

FillCannonCommand::FillCannonCommand() {
	// Use requires() here to declare subsystem dependencies
	Requires(cannonSubsystem);
}

// Called just before this Command runs the first time
void FillCannonCommand::Initialize() {
	printf("Fill start\n");

	cannonSubsystem->Fill();
}

// Called repeatedly when this Command is scheduled to run
void FillCannonCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool FillCannonCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FillCannonCommand::End() {
	printf("Fill end\n");
	cannonSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FillCannonCommand::Interrupted() {
	printf("Fill interrupted\n");
	cannonSubsystem->Stop();
}

#include "AtLoadingStationCommand.h"

AtLoadingStationCommand::AtLoadingStationCommand() {
	
}

// Called just before this Command runs the first time
void AtLoadingStationCommand::Initialize() {
	frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::Load);
}

// Called repeatedly when this Command is scheduled to run
void AtLoadingStationCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool AtLoadingStationCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AtLoadingStationCommand::End() {
	frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::ExitLoad);
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AtLoadingStationCommand::Interrupted() {
	frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::ExitLoad);
}

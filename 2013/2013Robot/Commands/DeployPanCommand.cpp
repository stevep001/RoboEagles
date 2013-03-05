#include "DeployPanCommand.h"

DeployPanCommand::DeployPanCommand() {

}

// Called just before this Command runs the first time
void DeployPanCommand::Initialize() {
	frisbeePanSubsystem->DeployPan();
}

// Called repeatedly when this Command is scheduled to run
void DeployPanCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool DeployPanCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void DeployPanCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeployPanCommand::Interrupted() {
}

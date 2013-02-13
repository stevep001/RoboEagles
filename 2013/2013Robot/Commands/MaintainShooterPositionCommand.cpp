#include "MaintainShooterPositionCommand.h"


MaintainShooterPositionCommand::MaintainShooterPositionCommand(float angle) {
	this->Requires(shooterTiltSubsystem);
	this->angle = angle;
}

// Called just before this Command runs the first time
void MaintainShooterPositionCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void MaintainShooterPositionCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool MaintainShooterPositionCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MaintainShooterPositionCommand::End() {
	pidController->Disable();
	delete this->pidController;
	this->pidController = NULL;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MaintainShooterPositionCommand::Interrupted() {
	pidController->Disable();
	delete this->pidController;
	this->pidController = NULL;
}

#include "SetShooterTiltCommand.h"

SetShooterTiltCommand::SetShooterTiltCommand(float angle) {
	printf("SetShooterTiltCommand: constructing\n");
	this->angle = angle;
	printf("SetShooterTiltCommand: constructed\n");
}

// Called just before this Command runs the first time
void SetShooterTiltCommand::Initialize() {
	shooterTiltSubsystem->SetAngle(this->angle);
}

// Called repeatedly when this Command is scheduled to run
void SetShooterTiltCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterTiltCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SetShooterTiltCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterTiltCommand::Interrupted() {
}

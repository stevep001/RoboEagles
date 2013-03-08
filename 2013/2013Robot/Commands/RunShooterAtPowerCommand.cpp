#include "RunShooterAtPowerCommand.h"

RunShooterAtPowerCommand::RunShooterAtPowerCommand(float power) {
	this->power = power;
}

// Called just before this Command runs the first time
void RunShooterAtPowerCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void RunShooterAtPowerCommand::Execute() {
	//shooterSubsystem->SetShootingPower(this->power);
}

// Make this return true when this Command no longer needs to run execute()
bool RunShooterAtPowerCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RunShooterAtPowerCommand::End() {
	//shooterSubsystem->SetShootingPower(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunShooterAtPowerCommand::Interrupted() {
	//shooterSubsystem->SetShootingPower(0);
}

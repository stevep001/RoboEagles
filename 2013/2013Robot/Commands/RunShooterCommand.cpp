#include "RunShooterCommand.h"

/**
 * Command to run shooter at specified power level
 */
RunShooterCommand::RunShooterCommand(float power) {
	Requires(shooterSubsystem);
	this->power = power;
}

// Called just before this Command runs the first time
void RunShooterCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void RunShooterCommand::Execute() {
	shooterSubsystem->SetShootingPower(power);
}

// Make this return true when this Command no longer needs to run execute()
bool RunShooterCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RunShooterCommand::End() {
	shooterSubsystem->SetShootingPower(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunShooterCommand::Interrupted() {
	shooterSubsystem->SetShootingPower(0);
}

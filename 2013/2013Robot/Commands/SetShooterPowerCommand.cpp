#include "SetShooterPowerCommand.h"

SetShooterPowerCommand::SetShooterPowerCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void SetShooterPowerCommand::Initialize() {
	switch (shooterSubsystem->GetShootingPower())
	{
	case ShooterSubsystem::Normal:
		shooterSubsystem->SetShootingPower(ShooterSubsystem::Low);
	default:
		shooterSubsystem->SetShootingPower(ShooterSubsystem::Normal);
		break;
	}
}

// Called repeatedly when this Command is scheduled to run
void SetShooterPowerCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterPowerCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SetShooterPowerCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterPowerCommand::Interrupted() {
}

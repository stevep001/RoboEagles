#include "SetTestShootingPowerCommand.h"

SetTestShootingPowerCommand::SetTestShootingPowerCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void SetTestShootingPowerCommand::Initialize() {
	shooterSubsystem->SetShootingPower(ShooterSubsystem::Test);
}

// Called repeatedly when this Command is scheduled to run
void SetTestShootingPowerCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool SetTestShootingPowerCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SetTestShootingPowerCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetTestShootingPowerCommand::Interrupted() {
}

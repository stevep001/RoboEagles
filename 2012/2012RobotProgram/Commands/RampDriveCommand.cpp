#include "RampDriveCommand.h"

RampDriveCommand::RampDriveCommand() : CommandBase("RampDriveCommand") {
	Requires(chassis);
}

// Called just before this Command runs the first time
void RampDriveCommand::Initialize() {
	chassis->enableBrakeMode();
}

// Called repeatedly when this Command is scheduled to run
void RampDriveCommand::Execute() {
	chassis->goStraight(oi->getRightJoystick()->GetY() * .8);
}

// Make this return true when this Command no longer needs to run execute()
bool RampDriveCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RampDriveCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RampDriveCommand::Interrupted() {
}

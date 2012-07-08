#include "HorizontalAimCommand.h"

HorizontalAimCommand::HorizontalAimCommand() {
	Requires(throwerSubsystem);
}

// Called just before this Command runs the first time
void HorizontalAimCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void HorizontalAimCommand::Execute() {
	double throwX = oi->getThrowJoystick()->GetX();
	if (throwX > 0.3 || throwX < -0.3) {
		throwerSubsystem->Move(throwX);
	}else{
		throwerSubsystem->Move(0);
	}
	
}

// Make this return true when this Command no longer needs to run execute()
bool HorizontalAimCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void HorizontalAimCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HorizontalAimCommand::Interrupted() {
	
}

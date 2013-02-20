#include "LiftPanCommand.h"

#define PAN_UP_POWER	(.4)
#define PAN_DOWN_POWER	(-.4)

LiftPanCommand::LiftPanCommand(bool up) {
	Requires(panLiftSubsystem);
	this->up = up; 
}

// Called just before this Command runs the first time
void LiftPanCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void LiftPanCommand::Execute() {
	if (this->up)
	{
		panLiftSubsystem->SetSpeed(PAN_UP_POWER);
	}
	else
	{
		panLiftSubsystem->SetSpeed(PAN_DOWN_POWER);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LiftPanCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LiftPanCommand::End() {
	panLiftSubsystem->SetSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftPanCommand::Interrupted() {
	panLiftSubsystem->SetSpeed(0);
}

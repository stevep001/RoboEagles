#include "LiftDownUntilTiltCommand.h"

// Change in pitch angle desired
#define	MIN_PITCH 5

LiftDownUntilTiltCommand::LiftDownUntilTiltCommand() {
	Requires(lifterSubsystem);
}

// Called just before this Command runs the first time
void LiftDownUntilTiltCommand::Initialize() {
	lifterSubsystem->LiftDown();
	this->finished = false;
	this->initialPitchAngle = sensorSubsystem->GetPitchGyroAngle();
}

// Called repeatedly when this Command is scheduled to run
void LiftDownUntilTiltCommand::Execute() {
	float currentPitchAngle = sensorSubsystem->GetPitchGyroAngle();
	float angleChange = currentPitchAngle - this->initialPitchAngle;
	printf("Angle change %f", angleChange);
	
	if (angleChange > MIN_PITCH || angleChange < -MIN_PITCH)
	{
		this->finished = true;
		lifterSubsystem->LiftStop();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LiftDownUntilTiltCommand::IsFinished() {
	return this->finished;
}

// Called once after isFinished returns true
void LiftDownUntilTiltCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftDownUntilTiltCommand::Interrupted() {
}

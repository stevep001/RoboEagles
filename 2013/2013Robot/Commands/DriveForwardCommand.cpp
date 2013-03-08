#include "DriveForwardCommand.h"

#define	DRIVING_POWER	(.7)
#define	FEET_PER_SEC_MAX			10
#define	MIN_POWER_TO_MOVE	(.3)

// This estimates the distance the robot will move once up to speed
#define FEET_PER_SEC	( (DRIVING_POWER - MIN_POWER_TO_MOVE) * FEET_PER_SEC_MAX )
#define	INCHES_PER_SEC	( FEET_PER_SEC * 12 )

// Estimate of how much time it takes robot to accelerate to speed
#define	TIME_TO_GET_GOING	(.3)

DriveForwardCommand::DriveForwardCommand(int distanceInInches) {
	Requires(chassis);
	this->distanceInInches = distanceInInches;
	this->timer = new Timer();
}

// Called just before this Command runs the first time
void DriveForwardCommand::Initialize() {
	this->timer->Reset();
	this->timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void DriveForwardCommand::Execute() {
	chassis->MoveForward(DRIVING_POWER);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForwardCommand::IsFinished() {
	// Estimate distance driven
	float estimatedInches = (timer->Get() - TIME_TO_GET_GOING) * INCHES_PER_SEC;
	return estimatedInches > this->distanceInInches;
}

// Called once after isFinished returns true
void DriveForwardCommand::End() {
	this->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForwardCommand::Interrupted() {
}

void DriveForwardCommand::Stop() {
	chassis->Stop();
	timer->Stop();
}

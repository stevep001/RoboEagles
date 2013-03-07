#include "TurnSpecifiedDegreesCommand.h"
#include "math.h"

// If we're within this # of degrees to target, then we're good.

#define DEGREES_PRECISION 2


/*
 * This command turns the number of degrees specified in the dashboard field.
 */
TurnSpecifiedDegreesCommand::TurnSpecifiedDegreesCommand(float degreesToTurn) 
	: CommandBase("TurnSpecifiedDegreesCommand") {
	Requires(chassis);
	this->degreesToTurn = degreesToTurn;
}

// Called just before this Command runs the first time
void TurnSpecifiedDegreesCommand::Initialize() {
	this->finished = false;
	this->startingAngle = sensorSubsystem->GetHorizontalAngle();
	this->goalAngle = startingAngle + this->degreesToTurn;
	printf("TurnSpecifiedDegreesCommand %f\n", this->degreesToTurn);
}

// Called repeatedly when this Command is scheduled to run
void TurnSpecifiedDegreesCommand::Execute() {
	float currentAngle = sensorSubsystem->GetHorizontalAngle();
	float angleDifference = goalAngle - currentAngle;
	
	SmartDashboard::PutNumber("Goal angle", goalAngle);
	SmartDashboard::PutNumber("Angle difference", fabs(angleDifference));
	printf("Angle difference %f goalAngle %f currentAngle %f\n", angleDifference, goalAngle, currentAngle);
	
	float turnRate = 0;
	
	if (fabs(angleDifference) < DEGREES_PRECISION) {
		chassis->Stop();
		finished = true;
	} else {
		// We slow our rate of turn as we get close to the angle we want.
		// These values are guesses.  A PID would be better here.
		if (angleDifference > 10 || angleDifference < -10) {
			turnRate = 0.7;
		} else {
			// Look at changing this at competition
			turnRate = 0.6;
		}
		
		SmartDashboard::PutNumber("turn rate", turnRate);
		
		if (angleDifference > 0) {
			chassis->TurnLeft(turnRate);
		} else {
			chassis->TurnRight(turnRate);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool TurnSpecifiedDegreesCommand::IsFinished() {
	return finished;	
}

// Called once after isFinished returns true
void TurnSpecifiedDegreesCommand::End() {
	printf("TurnSpecifiedDegreesCommand completed.\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnSpecifiedDegreesCommand::Interrupted() {
}

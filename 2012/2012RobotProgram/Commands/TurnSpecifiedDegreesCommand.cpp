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
	this->startingAngle = sensorSubsystem->GetYawGyroAngle();
	this->goalAngle = startingAngle + this->degreesToTurn;
	printf("TurnSpecifiedDegreesCommand %f\n", this->degreesToTurn);
}

// Called repeatedly when this Command is scheduled to run
void TurnSpecifiedDegreesCommand::Execute() {
	float currentAngle = sensorSubsystem->GetYawGyroAngle();
	float angleDifference = goalAngle - currentAngle;
	
	oi->getSmartDashboard()->PutDouble("Goal angle", goalAngle);
	oi->getSmartDashboard()->PutDouble("Angle difference", fabs(angleDifference));
	printf("Angle difference %f goalAngle %f currentAngle %f\n", angleDifference, goalAngle, currentAngle);
	
	float turnRate = 0;
	
	if (fabs(angleDifference) < DEGREES_PRECISION) {
		chassis->stop();
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
		
		oi->getSmartDashboard()->PutDouble("turn rate", turnRate);
		
		if (angleDifference > 0) {
			chassis->turnLeft(turnRate);
		} else {
			chassis->turnRight(turnRate);
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

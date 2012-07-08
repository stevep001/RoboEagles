#include "BallLoaderManualCommand.h"
#include "math.h"
#include "../RobotMap.h"

/**
 * This implements manual control of the ball loading process.
 */
BallLoaderManualCommand::BallLoaderManualCommand() : CommandBase("BallLoaderManualCommand"){
	Requires(ballLoaderSubsystem);
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void BallLoaderManualCommand::Initialize() {
	printf("Initializing BallLoaderManualCommand\n");
	ballLoaderSubsystem->BeltOff();
}

// Called repeatedly when this Command is scheduled to run
void BallLoaderManualCommand::Execute() {
	double BeltY = oi->getThrowJoystick()->GetY();
	//printf("BallLoaderCommand BeltY %f", BeltY);

	if (BeltY > 0.5){
		oi->getSmartDashboard()->PutString("belt", "going down");
		ballLoaderSubsystem->BeltDown();
	} else if (BeltY < -0.5){
		oi->getSmartDashboard()->PutString("belt", "going up");
		ballLoaderSubsystem->BeltUp();
	} else {
		oi->getSmartDashboard()->PutString("belt", "stopped");
		ballLoaderSubsystem->BeltOff();
	}
}


// Make this return true when this Command no longer needs to run execute()
bool BallLoaderManualCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void BallLoaderManualCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BallLoaderManualCommand::Interrupted() {
}

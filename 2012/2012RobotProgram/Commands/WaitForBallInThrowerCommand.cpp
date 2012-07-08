#include "WaitForBallInThrowerCommand.h"

WaitForBallInThrowerCommand::WaitForBallInThrowerCommand() : CommandBase("WaitForBallInThrowerCommand") {

}

// Called just before this Command runs the first time
void WaitForBallInThrowerCommand::Initialize() {
	finished = false;
	printf("Waiting for ball in thrower\n");
}

// Called repeatedly when this Command is scheduled to run
void WaitForBallInThrowerCommand::Execute() {
	if (sensorSubsystem->IsBallPresentSensor3()) {
		finished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool WaitForBallInThrowerCommand::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void WaitForBallInThrowerCommand::End() {
	printf("Done waiting for ball in thrower\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitForBallInThrowerCommand::Interrupted() {
}

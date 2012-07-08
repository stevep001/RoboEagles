#include "EjectBallsCommand.h"

EjectBallsCommand::EjectBallsCommand(float timeToEject) {
	Requires(ballLoaderSubsystem);
	printf("Initializing EjectBallsCommand\n");
	this->timeToEject = timeToEject;
	this->timer = new Timer();
	
}

// Called just before this Command runs the first time
void EjectBallsCommand::Initialize() {
	printf("EjectBallsCommand running\n");
	if(timer != NULL)
	{
		timer->Reset();
		timer->Start();
	}
	else
	{
		printf("Timer null?\n");
	}
}

// Called repeatedly when this Command is scheduled to run
void EjectBallsCommand::Execute() {
	ballLoaderSubsystem->BeltDown();	
}

// Make this return true when this Command no longer needs to run execute()
bool EjectBallsCommand::IsFinished() {
	if (timer == NULL)
	{
		return true;
	}
	else
	{
		return timer->Get() > timeToEject;
	}
}

// Called once after isFinished returns true
void EjectBallsCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EjectBallsCommand::Interrupted() {
}
